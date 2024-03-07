# Wind Simulation
본 프로젝트는 하기 참조 사이트를 기반으로, 본 제작자가 해석하여 만들었습니다.
- https://blog.mapbox.com/how-i-built-a-wind-map-with-webgl-b63022b5537f

### Video
- https://youtu.be/p5STJoc0wRI
<p align="center"> <img src="https://github.com/SonJunHyuck/Wind_Simulation/blob/main/videos/Wind%20Simulation%20with%20Compute%20Shader(Old).png" width="600" height="336"> </p>
<p align="center"> :arrow_down::arrow_down::arrow_down::arrow_down::arrow_down::arrow_down::arrow_down::arrow_down: </p>
<p align="center"> <img src="https://github.com/SonJunHyuck/Wind_Simulation/blob/main/videos/Wind%20Simulation%20with%20Compute%20Shader(New).png" width="600" height="336"> </p>

### How to build
그림 설명 : https://sonnysmile.notion.site/Wind-Simulation-ece1ff331abe444eb23320a7842c3d56?pvs=4

요약
1. Cmake -> Configure -> Visual Studio 17 2022 -> x64
2. Generate
3. Open Project (wind_simulatio.sln)
7. build

### Cmake Build Kit (for Visual code)
- Windows : Clang 16.0.5 (GNU CLI) for MSCV 17.8.34xxx (Visual Studio Tools 2022 Release - amd64)
  https://visualstudio.microsoft.com/ko/visual-cpp-build-tools/

- Mac (Silicon M2) do not support OpenGL430 (the least version to use compute shader)

### Refactoring (2024. 01)
- https://github.com/SonJunHyuck/OpenGL_BASIC
- 괜찮은 OpenGL Framework를 찾아, 본 프로젝트 리펙토링을 진행
