# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(FMS_database)

INCLUDE(${VISIT_SOURCE_DIR}/CMake/PluginMacros.cmake)

ADD_DATABASE_CODE_GEN_TARGETS(FMS)

SET(COMMON_SOURCES
FMSPluginInfo.C
FMSCommonPluginInfo.C
)

SET(LIBI_SOURCES
FMSPluginInfo.C
)

SET(LIBM_SOURCES
FMSMDServerPluginInfo.C
${COMMON_SOURCES}
avtFMSFileFormat.C
)

SET(LIBE_SOURCES
FMSEnginePluginInfo.C
${COMMON_SOURCES}
avtFMSFileFormat.C
)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${FMS_INCLUDE_DIR}
${MFEM_INCLUDE_DIR}
${VISIT_COMMON_INCLUDES}
${VISIT_INCLUDE_DIR}/avt/DBAtts/MetaData
${VISIT_INCLUDE_DIR}/avt/DBAtts/SIL
${VISIT_INCLUDE_DIR}/avt/Database/Database
${VISIT_INCLUDE_DIR}/avt/Database/Formats
${VISIT_INCLUDE_DIR}/avt/Database/Ghost
${VISIT_INCLUDE_DIR}/avt/FileWriter
${VISIT_INCLUDE_DIR}/avt/Filters
${VISIT_INCLUDE_DIR}/avt/MIR/Base
${VISIT_INCLUDE_DIR}/avt/MIR/Tet
${VISIT_INCLUDE_DIR}/avt/MIR/Zoo
${VISIT_INCLUDE_DIR}/avt/Math
${VISIT_INCLUDE_DIR}/avt/Pipeline/AbstractFilters
${VISIT_INCLUDE_DIR}/avt/Pipeline/Data
${VISIT_INCLUDE_DIR}/avt/Pipeline/Pipeline
${VISIT_INCLUDE_DIR}/avt/Pipeline/Sinks
${VISIT_INCLUDE_DIR}/avt/Pipeline/Sources
${VISIT_INCLUDE_DIR}/avt/VisWindow/VisWindow
${VISIT_INCLUDE_DIR}/visit_vtk/full
${VISIT_INCLUDE_DIR}/visit_vtk/lightweight
${VTK_INCLUDE_DIRS}
)

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} ${FMS_LIBRARY_DIR} ${MFEM_LIBRARY_DIR} )

ADD_LIBRARY(IFMSDatabase ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(IFMSDatabase visitcommon)
SET(INSTALLTARGETS IFMSDatabase)

IF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    ADD_LIBRARY(MFMSDatabase ${LIBM_SOURCES})
    TARGET_LINK_LIBRARIES(MFMSDatabase visitcommon avtdbatts avtdatabase_ser ${FMS_LIB} ${MFEM_LIB})
    ADD_TARGET_DEFINITIONS(MFMSDatabase MDSERVER)
    SET(INSTALLTARGETS ${INSTALLTARGETS} MFMSDatabase)
ENDIF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(EFMSDatabase_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(EFMSDatabase_ser visitcommon avtdatabase_ser avtpipeline_ser ${FMS_LIB} ${MFEM_LIB})
ADD_TARGET_DEFINITIONS(EFMSDatabase_ser ENGINE)
SET(INSTALLTARGETS ${INSTALLTARGETS} EFMSDatabase_ser)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(EFMSDatabase_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(EFMSDatabase_par visitcommon avtdatabase_par avtpipeline_par ${FMS_LIB} ${MFEM_LIB})
    ADD_TARGET_DEFINITIONS(EFMSDatabase_par ENGINE)
    SET(INSTALLTARGETS ${INSTALLTARGETS} EFMSDatabase_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_DATABASE_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(databases ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(databases FMS ${INSTALLTARGETS})
