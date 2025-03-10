set(PICOTTS_SRCS
  picopr.c
  picosa.c
  picokpr.c
  picodata.c
  picokfst.c
  picodbg.c
  picokdt.c
  picoctrl.c
  picoktab.c
  picoacph.c
  picokdbg.c
  #  picorsrc.c ### We use our custom esp_picorsrc.c instead
  picoos.c
  picospho.c
  picotok.c
  picosig.c
  picocep.c
  picofftsg.c
  picotrns.c
  picosig2.c
  picoextapi.c
  picopal.c
  picokpdf.c
  picobase.c
  picopam.c
  picowa.c
  picoklex.c
  picoapi.c
  picoknow.c
)
list(TRANSFORM PICOTTS_SRCS PREPEND "pico/lib/")


idf_component_register(
  SRCS
    "esp_picotts.c"
    "esp_picorsrc.c"
    ${PICOTTS_SRCS}
  INCLUDE_DIRS "include"
  PRIV_INCLUDE_DIRS "pico/lib"
  PRIV_REQUIRES "esp_partition"
)

# Suppress warnings in the library source
set_source_files_properties(
  ${PICOTTS_SRCS}
  PROPERTIES COMPILE_FLAGS
  "-Wno-implicit-fallthrough -Wno-unused-but-set-variable -Wno-unused-function"
)

# PicoTTS attempts to use exp() trickery which relies on a particular floating
# point representation format, which seemingly does not hold on Xtensa. As
# a workaround, we rename the picoos_quick_exp functin and provide our own
# wrapper back to standard math.h exp() instead.
set_source_files_properties(
  "pico/lib/picoos.c"
  PROPERTIES COMPILE_OPTIONS "-Dpicoos_quick_exp=picoos_quick_nope"
)

target_add_binary_data(${COMPONENT_LIB} ${COMPONENT_DIR}/pico/lang/picotts_ta.bin BINARY)
target_add_binary_data(${COMPONENT_LIB} ${COMPONENT_DIR}/pico/lang/picotts_sg.bin BINARY)


