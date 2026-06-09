# DESIGN

## 1. Overview
Parser for UAV telemetry data.

## 2. Objectives
- Parse telemetry data
- Detect anomalies
- Generate Reports

## 3. System Architecture

### Parser
Parses rows into structured objects.

### Validator
Uses parsed structured objects and validates user configured telemetry ranges.

### Anomaly Detector
Logs unusual data points based on user selected ranges.

### Report Generator
Structured and human readable logs including processing summary, invalid records, anomalies and statistics.

### Configuration
Configuration files to configure Validator and Anomaly ranges.

## 4. Class Design
Link to UML Diagram

## 5. Data Format
Simple CSV columns.

## 6. Error Handling
Log errors to console and include in report.

## 7. Testing
Unit tests for parser, validator, anomaly detection.

## 8. Future Improvements
- Support multiple file types
