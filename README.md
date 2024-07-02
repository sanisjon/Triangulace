# Panear Polygon Triangulation

This project focuses on the triangulation of polygons using both single-threaded and multi-threaded implementations. It includes performance comparisons between these implementations and provides SVG visualizations of the triangulated polygons.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [SVG Visualization](#svg-visualization)
- [Authors](#authors)
- [License](#license)

## Introduction

Panear Polygon Triangulation is a semestral project developed to compare the efficiency of single-threaded and multi-threaded implementations of polygon triangulation. The project also generates SVG visualizations to help users understand the triangulation process.

## Requirements

- C++17 or later
- CMake 3.10 or later
- Boost Libraries (for multi-threading)
- SVG library for C++ (such as SVG++)

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/sanisjon/PanearPolygonTriangulation.git
   cd PanearPolygonTriangulation
   
## Features

- **Single-threaded polygon triangulation**: Implementation of the polygon triangulation algorithm using a single thread.
- **Multi-threaded polygon triangulation**: Implementation of the polygon triangulation algorithm using multiple threads for improved performance.
- **Polygon generator**: Random polygon generator driverd by user inputs sutch ass min/max height, number of wertecies 
- **Performance comparison**: Tools to compare the execution time of single-threaded and multi-threaded implementations.
- **SVG visualization**: Generation of SVG files to visualize the triangulated polygons.

## Classes and Functions
**Graph**
- Represents the overall polygon data structure holding all polygon attributes

**ThreadGraph**
- A multithreaded version of the Graph class

**Vertex**
- Represents a point in the plane, holding information about its coordinates and a unique name.

**Triangle**
- Contains 3 polygon vertices; it is the product of the triangulation process.

**DataHelper**
- Helper class for running code comparison and listing to the Console.

## SVG Visualization

![t_image (1)](https://github.com/sanisjon/Triangulace/assets/149964539/dc3c54a2-50c4-4752-a6d2-2d87de5f086e)
<svg viewBox="-100 -500 1596 1000" xmlns='http://www.w3.org/2000/svg'>
<line x1="-100" y1="0" x2="1596" y2="0" stroke="#263238" stroke-width="3" stroke-dasharray="8,10" />
<line x1="0" y1="-500" x2="0" y2="1000" stroke="#263238" stroke-width="3" stroke-dasharray="8,10" />
<polygon points="0,350 0,-0 100,-140" stroke-width="1" stroke-dasharray="3,2"  stroke="black " fill="#00C853 " fill-opacity="0.8" />

<polygon points="100,-140 600,-300 700,250" stroke-width="1" stroke-dasharray="3,2"  stroke="black " fill="#009624 " fill-opacity="0.8" />

<polygon points="1100,-50 1200,-400 1300,-400" stroke-width="1" stroke-dasharray="3,2"  stroke="black " fill="#5EFC82 " fill-opacity="0.8" />

<polygon points="1300,-400 1360,300 1360,350" stroke-width="1" stroke-dasharray="3,2"  stroke="black " fill="#00C853 " fill-opacity="0.8" />

<polygon points="0,350 100,-140 700,250" stroke-width="1" stroke-dasharray="3,2"  stroke="black " fill="#009624 " fill-opacity="0.8" />

<polygon points="1000,150 1100,-50 1300,-400" stroke-width="1" stroke-dasharray="3,2"  stroke="black " fill="#5EFC82 " fill-opacity="0.8" />

<polygon points="1360,350 0,350 700,250" stroke-width="1" stroke-dasharray="3,2"  stroke="black " fill="#00C853 " fill-opacity="0.8" />

<polygon points="1000,150 1300,-400 1360,350" stroke-width="1" stroke-dasharray="3,2"  stroke="black " fill="#009624 " fill-opacity="0.8" />

<polygon points="1360,350 700,250 1000,150" stroke-width="1" stroke-dasharray="3,2"  stroke="black " fill="#5EFC82 " fill-opacity="0.8" />

<polygon points="0.000000,350.000000 0.000000,-0.000000 200.000000,-50.000000 300.000000,-50.000000 400.000000,50.000000 500.000000,300.000000 1360.000000,300.000000 1360.000000,350.000000 " stroke="CFD8DC" stroke-width="1" fill= " white "  fill-opacity="1" />
<line x1="-100" y1="0" x2="1596" y2="0" stroke="#263238" stroke-width="3" stroke-dasharray="8,10" />
<line x1="0" y1="-500" x2="0" y2="1000" stroke="#263238" stroke-width="3" stroke-dasharray="8,10" />
<polygon points="0,350 0,-0 200,-50" stroke-width="1" stroke-dasharray="3,2"  stroke="#D50000 " fill="#CFD8DC " fill-opacity="0.8" />

<polygon points="200,-50 300,-50 400,50" stroke-width="1" stroke-dasharray="3,2"  stroke="#D50000 " fill="#CFD8DC " fill-opacity="0.8" />

<polygon points="500,300 1360,300 1360,350" stroke-width="1" stroke-dasharray="3,2"  stroke="#D50000 " fill="#CFD8DC " fill-opacity="0.8" />

<polygon points="0,350 200,-50 400,50" stroke-width="1" stroke-dasharray="3,2"  stroke="#D50000 " fill="#CFD8DC " fill-opacity="0.8" />

<polygon points="500,300 1360,350 0,350" stroke-width="1" stroke-dasharray="3,2"  stroke="#D50000 " fill="#CFD8DC " fill-opacity="0.8" />

<polygon points="500,300 0,350 400,50" stroke-width="1" stroke-dasharray="3,2"  stroke="#D50000 " fill="#CFD8DC " fill-opacity="0.8" />

<line x1="0" y1="350" x2="0" y2="-0" stroke="blue" stroke-width="2" />
<line x1="0" y1="-0" x2="100" y2="-140" stroke="blue" stroke-width="2" />
<line x1="100" y1="-140" x2="600" y2="-300" stroke="blue" stroke-width="2" />
<line x1="600" y1="-300" x2="700" y2="250" stroke="blue" stroke-width="2" />
<line x1="700" y1="250" x2="1000" y2="150" stroke="blue" stroke-width="2" />
<line x1="1000" y1="150" x2="1100" y2="-50" stroke="blue" stroke-width="2" />
<line x1="1100" y1="-50" x2="1200" y2="-400" stroke="blue" stroke-width="2" />
<line x1="1200" y1="-400" x2="1300" y2="-400" stroke="blue" stroke-width="2" />
<line x1="1300" y1="-400" x2="1360" y2="300" stroke="blue" stroke-width="2" />
<line x1="1360" y1="300" x2="1360" y2="350" stroke="blue" stroke-width="2" />
<line x1="0" y1="350" x2="1360" y2="350" stroke="green" stroke-width="2" />
<circle cx="0" cy="350" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="0" y="353" text-anchor="middle" font-size="12" font-weight="bold">A</text>
<circle cx="0" cy="-0" r="10" stroke="#0026CA" stroke-width="2" fill="#84FFFF" />
<text x="0" y="3" text-anchor="middle" font-size="12" font-weight="bold">0</text>
<circle cx="100" cy="-140" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="100" y="-137" text-anchor="middle" font-size="12" font-weight="bold">1</text>
<circle cx="600" cy="-300" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="600" y="-297" text-anchor="middle" font-size="12" font-weight="bold">2</text>
<circle cx="700" cy="250" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="700" y="253" text-anchor="middle" font-size="12" font-weight="bold">3</text>
<circle cx="1000" cy="150" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="1000" y="153" text-anchor="middle" font-size="12" font-weight="bold">4</text>
<circle cx="1100" cy="-50" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="1100" y="-47" text-anchor="middle" font-size="12" font-weight="bold">5</text>
<circle cx="1200" cy="-400" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="1200" y="-397" text-anchor="middle" font-size="12" font-weight="bold">6</text>
<circle cx="1300" cy="-400" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="1300" y="-397" text-anchor="middle" font-size="12" font-weight="bold">7</text>
<circle cx="1360" cy="300" r="10" stroke="#0026CA" stroke-width="2" fill="#84FFFF" />
<text x="1360" y="303" text-anchor="middle" font-size="12" font-weight="bold">8</text>
<circle cx="1360" cy="350" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="1360" y="353" text-anchor="middle" font-size="12" font-weight="bold">B</text>
<line x1="0" y1="350" x2="0" y2="-0" stroke="red" stroke-width="2" />
<line x1="0" y1="-0" x2="200" y2="-50" stroke="red" stroke-width="2" />
<line x1="200" y1="-50" x2="300" y2="-50" stroke="red" stroke-width="2" />
<line x1="300" y1="-50" x2="400" y2="50" stroke="red" stroke-width="2" />
<line x1="400" y1="50" x2="500" y2="300" stroke="red" stroke-width="2" />
<line x1="500" y1="300" x2="1360" y2="300" stroke="red" stroke-width="2" />
<line x1="1360" y1="300" x2="1360" y2="350" stroke="red" stroke-width="2" />
<line x1="0" y1="350" x2="1360" y2="350" stroke="green" stroke-width="2" />
<circle cx="0" cy="350" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="0" y="353" text-anchor="middle" font-size="12" font-weight="bold">A</text>
<circle cx="0" cy="-0" r="10" stroke="#0026CA" stroke-width="2" fill="#84FFFF" />
<text x="0" y="3" text-anchor="middle" font-size="12" font-weight="bold">0</text>
<circle cx="200" cy="-50" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="200" y="-47" text-anchor="middle" font-size="12" font-weight="bold">14</text>
<circle cx="300" cy="-50" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="300" y="-47" text-anchor="middle" font-size="12" font-weight="bold">13</text>
<circle cx="400" cy="50" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="400" y="53" text-anchor="middle" font-size="12" font-weight="bold">12</text>
<circle cx="500" cy="300" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="500" y="303" text-anchor="middle" font-size="12" font-weight="bold">11</text>
<circle cx="1360" cy="300" r="10" stroke="#0026CA" stroke-width="2" fill="#84FFFF" />
<text x="1360" y="303" text-anchor="middle" font-size="12" font-weight="bold">8</text>
<circle cx="1360" cy="350" r="10" stroke="Black" stroke-width="2" fill="white" />
<text x="1360" y="353" text-anchor="middle" font-size="12" font-weight="bold">B</text>
<circle cx="0" cy="-0" r="10" stroke="#0026CA" stroke-width="2" fill="#84FFFF" />
<text x="0" y="3" text-anchor="middle" font-size="12" font-weight="bold">0</text>
<circle cx="1360" cy="300" r="10" stroke="#0026CA" stroke-width="2" fill="#84FFFF" />
<text x="1360" y="303" text-anchor="middle" font-size="12" font-weight="bold">8</text>
</svg>
