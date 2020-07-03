cmake_minimum_required(VERSION 2.8)
project(proto_file)

include_directories(proto_file)
set(BASE_EXTERN ${CMAKE_SOURCE_DIR}/../../public/lib)
include(../../tools/cmake/Config.cmake)

set(TOPDIR ${CMAKE_SOURCE_DIR}/../../)

#set(INSTALL_TO ${INSTALL_TO})

## cross platform need reset protoc position
## we only support compile corei7 in ubuntu, so the path use x64.
set(PROTOC_DIR ${protobuf_base})
if("${PLATFORM}" STREQUAL "corei7")
    set(protobuf_base_not_corei7 ${protobuf_base}/../x64)
    set(ENV{PATH} "$ENV{PATH}:${protobuf_base_not_corei7}/bin:")
    set(ENV{LD_LIBRARY_PATH} "$ENV{LD_LIBRARY_PATH}:${protobuf_base_not_corei7}/lib:")
    set(PROTOC_DIR ${protobuf_base}/../x64)
else()
    set(ENV{PATH} "$ENV{PATH}:${protobuf_base}/bin:")
    set(ENV{LD_LIBRARY_PATH} "$ENV{LD_LIBRARY_PATH}:${protobuf_base}/lib:")
endif()
set(PROTOC ${PROTOC_DIR}/bin/protoc)
set(PROTOBUF_FILE_PATH ${TOPDIR}/library)
execute_process(COMMAND chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/gen_proto.sh)
execute_process(COMMAND rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/proto_file)
execute_process(COMMAND mkdir ${CMAKE_CURRENT_SOURCE_DIR}/proto_file)
execute_process(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/gen_proto.sh ${PROTOC} ${PROTOBUF_FILE_PATH}/proto_file ${CMAKE_CURRENT_SOURCE_DIR}/proto_file)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/proto_file AUX_SOURCE_FILE)

set(PROTO_SOURCE_FILE
        ${AUX_SOURCE_FILE}
        )



set(PROTO_SOURCE_HEADER_FILE
		proto_file/Proto.h
        proto_file/AlarmType.pb.h
        proto_file/CatalogBean.pb.h
        proto_file/DataType.pb.h
        proto_file/GetBoxInfo.pb.h
        proto_file/ModuleType.pb.h
        proto_file/ParamListBean.pb.h
        proto_file/ParamMessageBean.pb.h
        proto_file/ServiceRegisterBean.pb.h
        proto_file/ResultMassageBean.pb.h
        proto_file/LinkDevAndServiceBean.pb.h
        proto_file/DevInfoListBean.pb.h
        proto_file/MediaBean.pb.h
        proto_file/MeetingMessageBean.pb.h
        proto_file/ActionLinkBean.pb.h
        proto_file/MSDevUpdateFromDIS.pb.h
        proto_file/AlarmBean.pb.h
        proto_file/HbeaconDataBean.pb.h
        proto_file/SignInDataBean.pb.h
        proto_file/WristBandMacListBean.pb.h
        proto_file/DataDistributeBean.pb.h
		proto_file/VideoBean.pb.h
        )

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/build OTHER_SOURCE_FILE)
set(OTHER_FILE
        ${OTHER_SOURCE_FILE}
        )

set(OTHER_HEADER_FILE
        build/Proto.h
        )

set(OUTPUTNAME ${PROJECT_NAME}${D_SUFFIX})

add_library(${PROJECT_NAME}_static STATIC ${PROTO_SOURCE_FILE} ${OTHER_FILE})
add_library(${PROJECT_NAME} SHARED ${PROTO_SOURCE_FILE} ${OTHER_FILE})

SET_TARGET_PROPERTIES(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${OUTPUTNAME})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${OUTPUTNAME})
set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(${PROJECT_NAME}_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0.1 SOVERSION 1)

install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_TO}${PROJECT_NAME}/${PLATFORM}/lib)
#install(TARGETS ${PROJECT_NAME} DESTINATION ${FILESYS}/${PLATFORM}/usr/lib)
install(TARGETS ${PROJECT_NAME}_static DESTINATION ${INSTALL_TO}${PROJECT_NAME}/${PLATFORM}/lib)
#install(FILES ${PROTO_SOURCE_HEADER_FILE} DESTINATION ${INSTALL_TO}${PROJECT_NAME}/${PLATFORM}/include)
install(DIRECTORY proto_file/ DESTINATION ${INSTALL_TO}${PROJECT_NAME}/${PLATFORM}/include
    FILES_MATCHING PATTERN "*.h")
install(DIRECTORY build/ DESTINATION ${INSTALL_TO}${PROJECT_NAME}/${PLATFORM}/include
    FILES_MATCHING PATTERN "*.h")

