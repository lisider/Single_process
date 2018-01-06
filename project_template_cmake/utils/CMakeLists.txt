
ADD_SUBDIRECTORY(alsa)
ADD_SUBDIRECTORY(cjson)
ADD_SUBDIRECTORY(control)
ADD_SUBDIRECTORY(database)
ADD_SUBDIRECTORY(datalist)
ADD_SUBDIRECTORY(mystr)
ADD_SUBDIRECTORY(ringbuf)
ADD_SUBDIRECTORY(wav_parser)
ADD_SUBDIRECTORY(wifi)



AUX_SOURCE_DIRECTORY(. DIR_SRCS)
add_library(utils ${DIR_SRCS})

TARGET_LINK_LIBRARIES(utils alsa cjson control database datalist mystr ringbuf wav_parser wifi)

