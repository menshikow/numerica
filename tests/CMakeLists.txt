add_executable(numerica_tests
  test_smoke.cpp
)

target_link_libraries(numerica_tests
  PRIVATE numerica::numerica
)

if (MSVC)
  target_compile_options(numerica_tests PRIVATE /W4 /permissive-)
else()
  target_compile_options(numerica_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME numerica.smoke COMMAND numerica_tests)
