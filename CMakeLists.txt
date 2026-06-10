cmake_minimum_required(VERSION 4.3.0)

project(TelemetryLogParser)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    TelemetryData.cpp
    TelemetryParser.cpp
    TelemetryValidator.cpp
    TelemetryAnomaly.cpp
    ConfigParser.cpp
)
