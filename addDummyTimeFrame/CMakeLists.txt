cmake_minimum_required(VERSION 3.10)
project(addDummyTimeFrame)

find_package(ROOT REQUIRED)
find_package(podio REQUIRED)
find_package(EDM4HEP REQUIRED)
find_package(EDM4EIC REQUIRED)

include_directories(/opt/local/podio/include)

include_directories(
    ${ROOT_INCLUDE_DIRS}
    ${podio_INCLUDE_DIRS}
    ${edm4hep_INCLUDE_DIRS}
    ${edm4eic_INCLUDE_DIRS}
)


add_executable(addDummyTimeFrame addDummyTimeFrame.cc)



target_link_libraries(addDummyTimeFrame
     ${ROOT_LIBRARIES}
    podio::podio
    podio::podioRootIO
    EDM4HEP::edm4hep
    EDM4EIC::edm4eic
)

