include(FetchContent)

function (load_agloader)
  FetchContent_Declare(
    agloader
    GIT_REPOSITORY https://github.com/LeDYoM/agloader.git
    GIT_TAG rc_0.3.1.7
  )

  FetchContent_MakeAvailable(agloader)
endfunction()
