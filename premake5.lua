
newoption
{
    trigger = "graphics",
    value = "OPENGL_VERSION",
    description = "version of OpenGL to build raylib against",
    allowed = {
        { "opengl11", "OpenGL 1.1"},
        { "opengl21", "OpenGL 2.1"},
        { "opengl33", "OpenGL 3.3"},
        { "opengl43", "OpenGL 4.3"}
    },
    default = "opengl33"
}

function define_C()
    language "C"
end

function define_Cpp()
    language "C++"
end

function string.starts(String,Start)
    return string.sub(String,1,string.len(Start))==Start
end

function link_to(lib)
    links (lib)
    includedirs ("../"..lib.."/include")
    includedirs ("../"..lib.."/" )
end

function download_progress(total, current)
    local ratio = current / total;
    ratio = math.min(math.max(ratio, 0), 1);
    local percent = math.floor(ratio * 100);
    print("Download progress (" .. percent .. "%/100%)")
end

function download_file(url, filename, is_zip)
    print(filename .." not found, downloading from " .. url)
    local result_str, response_code = http.download(url, filename, {
        progress = download_progress,
        headers = { "From: Premake", "Referer: Premake" }
    })
    if result_str == nil then
        print("Download failed!")
        return
    end
    if is_zip then
        print("Unzipping to " ..  os.getcwd())
        zip.extract(filename, os.getcwd())
        os.remove(filename)
    end
end

function check_raylib()
    if(not os.isdir("raylib-master")) then
        download_file("https://github.com/raysan5/raylib/archive/refs/heads/master.zip", "raylib-master.zip", true)
    end
end

function check_raylib_cpp()
    if(not os.isfile("include/raylib-cpp.hpp")) then
        download_file("https://github.com/RobLoach/raylib-cpp/archive/master.zip", "raylib-cpp-master.zip", true)
    end
    local files = os.matchfiles("raylib-cpp-master/include/*")
    for _, file in ipairs(files) do
        if path.getname(file) ~= "CMakeLists.txt" then
            os.copyfile(file, "include/" .. path.getname(file))
        end
    end
end

function check_exprtk()
    if(not os.isfile("include/exprtk.hpp")) then
        download_file("https://www.partow.net/downloads/exprtk.zip", "exprtk.zip", true)
    end
    os.copyfile("exprtk/exprtk.hpp", "include/exprtk.hpp")
end

function check_json()
    if(not os.isfile("include/json.hpp")) then
        download_file("https://raw.githubusercontent.com/nlohmann/json/master/single_include/nlohmann/json.hpp", "json.hpp", false)
    end
    os.copyfile("json.hpp", "include/json.hpp")
    os.remove("json.hpp")
end

function check_lib()
    check_raylib();
    check_raylib_cpp();
    check_exprtk();
    check_json();
end

workspaceName = path.getbasename(os.getcwd())

if (string.lower(workspaceName) == "raylib") then
    print("raylib is a reserved name. Name your project directory something else.")
    -- Project generation will succeed, but compilation will definitely fail, so just abort here.
    os.exit()
end

workspace (workspaceName)
    configurations { "Debug", "Release"}
    platforms { "x64", "x86"}
    buildoptions {"/bigobj"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:x64" }
        architecture "x86_64"

    filter {}

    targetdir "_bin/%{cfg.buildcfg}/"

    if(os.isdir("src")) then
        startproject(workspaceName)
    end

    cdialect "C99"
    cppdialect "C++20"
	check_lib();

	include ("raylib_premake5.lua")

	if(os.isdir("src")) then
		include ("src")
	end


