add_rules("mode.debug", "mode.release")

target("main")
    add_files("src/*.cpp")
    add_vectorexts("sse2", "sse3", "ssse3", "avx", "avx2")
    set_languages("clatest", "cxxlatest")
    --set_warnings("everything")
    --set_toolchains("mingw")
    set_toolchains("clang-cl")
    --set_toolchains("msvc")
    if is_mode("release") then
        add_defines("NDEBUG", "_NDEBUG")
        set_optimize("faster")
        set_strip("all")
    else
        add_defines("DEBUG", "_DEBUG")
        set_symbols("debug")
    end
