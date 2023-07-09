#include "RaylibUtils.h"
#include <charconv>
#include "../System/GlobalVariable.h"

int RaylibUtils::getWindowWidth()
{
    if (IsWindowFullscreen())
    {
        return GetMonitorWidth(GetCurrentMonitor());
    }
	return GetScreenWidth();
}

int RaylibUtils::getWindowHeight()
{
    if (IsWindowFullscreen())
    {
        return GetMonitorHeight(GetCurrentMonitor());
    }
    return GetScreenHeight();
}

float RaylibUtils::getRealLength(const float length)
{
    return length * zoomPercent;
}

float RaylibUtils::getRealLength(const int length)
{
    return static_cast<float>(length) * zoomPercent;
}

Vector2 RaylibUtils::getRealLength(Vector2 vector2)
{
	vector2.x *= zoomPercent;
	vector2.y *= zoomPercent;
	return vector2;
}

Rectangle RaylibUtils::getRealLength(Rectangle rec)
{
    rec.x *= zoomPercent;
	rec.y *= zoomPercent;
	rec.width *= zoomPercent;
	rec.height *= zoomPercent;
	return rec;
}

bool RaylibUtils::checkCollisionPointRecs(const raylib::Vector2& point,
    const std::vector<raylib::Rectangle>& recs)
{
    for (const auto& rec : recs)
    {
    	if (CheckCollisionPointRec(point, rec))
    	{
    		return true;
		}
	}
	return false;
}

std::vector<int> RaylibUtils::hexDecode(const std::string& str, unsigned char charsPerNum)
{
    std::vector out(str.size() / charsPerNum, 0);

    int value;
    for (std::size_t i = 0; i < str.size() / charsPerNum; i++) {
        std::from_chars(
            str.data() + (i * charsPerNum),
            str.data() + (i * charsPerNum) + charsPerNum,
            value,
            16
        );
        out[i] = value;
    }
    return out;
}

raylib::Font RaylibUtils::getContainTextFont(const std::string& fileName, const std::string& text)
{
    std::string str = text;
    str.append("0123456789");
    int codepointCount = 0;
    int* codepoints = LoadCodepoints(str.c_str(), &codepointCount);

    int codepointsNoDupsCount = 0;
    int* codepointsNoDups = codepointRemoveDuplicates(codepoints, codepointCount, &codepointsNoDupsCount);
    UnloadCodepoints(codepoints);

    raylib::Font font = LoadFontEx(fileName.c_str(), 64, codepointsNoDups, codepointsNoDupsCount);
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    free(codepointsNoDups);
    return font;
}

int* RaylibUtils::codepointRemoveDuplicates(const int* codepoints, const int codepointCount, int* codepointsResultCount)
{
    int codepointsNoDupsCount = codepointCount;
    const auto codepointsNoDups = static_cast<int*>(calloc(codepointCount, sizeof(int)));
    memcpy(codepointsNoDups, codepoints, codepointCount * sizeof(int));

    // Remove duplicates
    for (int i = 0; i < codepointsNoDupsCount; i++)
    {
        for (int j = i + 1; j < codepointsNoDupsCount; j++)
        {
            if (codepointsNoDups[i] == codepointsNoDups[j])
            {
                for (int k = j; k < codepointsNoDupsCount; k++) codepointsNoDups[k] = codepointsNoDups[k + 1];

                codepointsNoDupsCount--;
                j--;
            }
        }
    }

    // NOTE: The size of codepointsNoDups is the same as original array but
    // only required positions are filled (codepointsNoDupsCount)

    *codepointsResultCount = codepointsNoDupsCount;
    return codepointsNoDups;
}

// Draw text using font inside rectangle limits with support for text selection
void RaylibUtils::drawTextBoxed(const raylib::Font& font, const std::string& text, const Rectangle rec, const float fontSize, const float spacing, const bool wordWrap, const Color tint)
{
	const int length = TextLength(text.c_str());  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

	const float scaleFactor = fontSize / static_cast<float>(font.baseSize);     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap ? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        const int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        const int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width * scaleFactor : font.glyphs[index].advanceX * scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container.
        if (state == MEASURE_STATE)
        {
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1) ? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + static_cast<float>(font.baseSize) / 2) * scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + static_cast<float>(font.baseSize) / 2) * scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize * scaleFactor) > rec.height) break;

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                	DrawTextCodepoint(font, codepoint, Vector2(rec.x + textOffsetX, rec.y + textOffsetY), fontSize, tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + static_cast<float>(font.baseSize) / 2) * scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
}
