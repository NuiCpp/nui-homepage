function(set_common_options TARGET)
    set(COMMON_OPTIONS -fexceptions -Wall -pedantic-errors -pedantic -fconstexpr-steps=1271242)
    set(DEBUG_OPTIONS  -g ${COMMON_OPTIONS})
    set(RELEASE_OPTIONS -O3 ${COMMON_OPTIONS})
    target_compile_options(${TARGET} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
    target_compile_options(${TARGET} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
endfunction()