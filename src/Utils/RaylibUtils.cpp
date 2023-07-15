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
