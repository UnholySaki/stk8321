#
# Copyright (c) 2024 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(nrf_connect_sdk_intermediate)

FILE(GLOB app_sources src/*.c)
FILE(GLOB lib_sources ../../../src/*.c)

target_sources(app PRIVATE ${app_sources})
target_sources(app PRIVATE ${lib_sources})
