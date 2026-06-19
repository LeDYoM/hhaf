include(FetchContent)

function (load_agloader)
  FetchContent_Declare(
    agloader
    GIT_REPOSITORY https://github.com/LeDYoM/agloader.git
    GIT_TAG main
  )

  FetchContent_MakeAvailable(agloader)
endfunction()
