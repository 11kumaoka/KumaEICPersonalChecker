cmake_minimum_required(VERSION 3.16)

project(EventAna LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ROOT REQUIRED)
find_package(podio REQUIRED)
find_package(EDM4EIC REQUIRED)
find_package(EDM4HEP REQUIRED)
add_executable(EventAna main.cc EventAna.cc ValueReader.cc)

target_include_directories(EventAna PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(EventAna
  ${ROOT_LIBRARIES}
  podio::podio
  podio::podioRootIO
  EDM4EIC::edm4eic
  EDM4HEP::edm4hep
)