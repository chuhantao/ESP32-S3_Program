# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Espressif/frameworks/esp-idf-v5.1.2/components/bootloader/subproject"
  "D:/CODE/ESP32-S3_Program/ESP_IOT_demotest/build/bootloader"
  "D:/CODE/ESP32-S3_Program/ESP_IOT_demotest/build/bootloader-prefix"
  "D:/CODE/ESP32-S3_Program/ESP_IOT_demotest/build/bootloader-prefix/tmp"
  "D:/CODE/ESP32-S3_Program/ESP_IOT_demotest/build/bootloader-prefix/src/bootloader-stamp"
  "D:/CODE/ESP32-S3_Program/ESP_IOT_demotest/build/bootloader-prefix/src"
  "D:/CODE/ESP32-S3_Program/ESP_IOT_demotest/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/CODE/ESP32-S3_Program/ESP_IOT_demotest/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/CODE/ESP32-S3_Program/ESP_IOT_demotest/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
