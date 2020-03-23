#configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/../config.h" @ONLY)

add_executable(
    heliostat 
    	main.cpp
	ser.cpp
	image_processing.cpp
)
SET_TARGET_PROPERTIES(heliostat PROPERTIES
  LINK_FLAGS "-lopencv_dnn -lopencv_ml -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core"
)

install(
	TARGETS heliostat 
	RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
)
