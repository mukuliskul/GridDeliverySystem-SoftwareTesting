# GridDeliverySystem Documentation

## Overview

This document outlines the framework and objectives of a software project designed to manage package deliveries within a city grid. The project involves the simulation of delivery routes and the optimization of package allocation to various delivery trucks based on specific constraints and requirements.

### Project Scope

- **City Grid Representation:** A 25x25 square grid modeling the city.
- **Trucks and Routes:** Three trucks with distinct routes (blue, yellow, green) starting from the office location at grid square 1A.
- **Truck Specifications:** Each truck has a capacity limit of 1000 kg and 36 cubic meters.
- **Package Specifications:** Packages vary in size (1/4, 1/2, 1 cubic meter) and weight.

### Objectives

The primary objective is to efficiently assign shipments to the appropriate trucks while minimizing route deviations. This involves calculating the proximity of each truck to the intended delivery destination and considering the truck's remaining capacity.

## Distance Calculation Methodology

- **Euclidean Geometry:** Employ Euclidean geometry to ascertain the shortest path for potential route diversions, taking into account the city grid and building obstructions.

## Algorithm for Shortest Path

- **A\* Algorithm Usage:** Implement the A\* algorithm to navigate the shortest path to the destination, avoiding building structures and not retracing steps.

## Comprehensive Algorithm

- **Route and Capacity Tracking:** Continuously monitor each truck's route and available capacity.
- **Shortest Path Determination:** Identify the truck that offers the shortest diversion from its route to the destination.
- **Package Allocation:** Allocate shipments based on truck proximity and capacity constraints, marking destinations as unreachable when necessary.

## Project Deliverables

- **Code and Documentation Storage:** Utilize Git for storing all code-related work.
- **Function and Change Documentation:** All data structures, functions, and changes should be thoroughly documented.
- **Task Management:** Leverage Jira for managing tasks, tracking progress, and conducting scrum meetings.
- **Directory Structure Maintenance:** Adhere to the predefined repository directory structure for scrum reports and other documents.

## Evaluation Criteria

- **Individual Contribution & Team Collaboration:** Evaluated based on the extent and quality of individual contributions and effective teamwork.
- **Deadline Adherence & Work Quality:** Focus on meeting project timelines with high-quality outputs.
- **Testing Rigor & Documentation:** Emphasis on comprehensive testing and meticulous documentation.

## Milestone Descriptions

- **Milestone 2:** Focus on problem analysis, data structure additions, and test plan creation.
- **Milestone 3:** Develop detailed function specifications.
- **Milestone 4:** Complete function implementation, execute black-box tests, and develop white-box tests.
- **Milestone 5:** Develop, implement, and execute integration and acceptance tests.
- **Milestone 6:** Conduct final acceptance testing, bug resolution, testing report compilation, and test matrix review.

## Additional Resources

### Team Collaboration and Testing Details

For a detailed insight into our team's collaborative efforts, individual contributions, and specific testing methodologies implemented throughout the project, please refer to our **[Testing and Collaboration Documentation](./TestingAndCollaboration.md)**.

This document provides an in-depth view of how our team navigated the challenges of software testing, including black-box and white-box testing strategies, and the collaborative process that guided our progress and decisions from inception to completion. It also includes personal reflections and learning experiences from me, emphasizing my journey towards achieving our project goals.
