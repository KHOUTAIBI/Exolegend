# Exolegend

Welcome to the **Exolegend** repository! This project contains C++ code and resources for the Exolegend robotic programming competition, a thrilling hackathon where teams program autonomous "Gladiator" robots to dominate a maze-like arena. This codebase is designed to help participants develop, test, and deploy strategies for the Exolegend 2024 challenge.

## About Exolegend

Exolegend is a robotic programming competition organized by Exotec. Teams program autonomous robots, called "Gladiators," to navigate a dynamic arena, capture territory using colored paint (yellow or blue), and outsmart opponents. The competition emphasizes skills in C++ programming, real-time embedded systems, and strategic teamwork. Visit [exolegend.com](https://www.exolegend.com/) for more details.

This repository provides a framework for programming Gladiator robots, including example code and utilities for the Exolegend environment.

## Features

- **Robot Control**: C++ code for controlling Gladiator robots on an ESP32 processor.
- **Navigation Algorithms**: Logic for maze navigation and territory capture.
- **Modular Codebase**: Easy-to-extend structure for custom strategies.
- **Example Programs**: Sample code to learn robot movements and sensor usage.
- **Documentation**: Guides for setup and deployment.

## Getting Started

### Prerequisites

To use this repository, you’ll need:
- **C++ Compiler**: Supports C++11 or later (e.g., GCC, Clang).
- **ESP32 Development Environment**: Arduino IDE or PlatformIO with ESP32 support.
- **Exolegend Library**: Provided by competition organizers (available at [exolegend.com](https://www.exolegend.com/)).
- **Hardware** (optional): ESP32-based Gladiator robot for deployment.
- **Git**: For cloning the repository.

### Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/KHOUTAIBI/Exolegend.git
   cd Exolegend
   ```
2. **Install Dependencies**:
  - Set up ESP32 support in your IDE (e.g., Arduino IDE or PlatformIO).
  - Download the Exolegend library from the competition site and place it in the lib/ folder.

### File Structure
Exolegend/
├── src/                  # Source code for robot control  
│   ├── main.cpp          # Main program  
│   └── strategies/       # Strategy implementations  
├── examples/             # Example programs  
├── lib/                  # Exolegend library and dependencies  
├── docs/                 # Documentation  
├── config.h              # Configuration file  
└── README.md             # This file  
