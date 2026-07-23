# Project Smart Car — AI agent guidance

This repository is a PlatformIO-based ESP32 Arduino project for a Smart Car template.

## What this project is
- Root entrypoint: `src/main.cpp`.
- Build system: PlatformIO via `platformio.ini`.
- Target board: `esp-wrover-kit` with `framework = arduino`.
- Local libraries are stored in `lib/`; project headers belong in `include/`.

## Build and validation
- Compile: `platformio run -e esp-wrover-kit`
- Upload: `platformio run -e esp-wrover-kit -t upload`
- Monitor serial output: `platformio device monitor -b 115200`

## Key files and directories
- `platformio.ini` — board and build configuration.
- `src/` — main project source.
- `include/` — shared project headers.
- `lib/` — local libraries, including `acebott`, `ESP32Servo`, and `IRremote`.
- `test/` — currently contains only documentation, no active test harness is configured.

## Agent behavior guidance
- Keep changes minimal and aligned to the user request.
- Use `platformio run -e esp-wrover-kit` to verify code compiles.
- Avoid broad refactors across embedded third-party libraries in `lib/` unless explicitly requested.
- Prefer project-local fixes in `src/` and `include/`.
- Do not assume a desktop or non-ESP32 environment; target ESP32 Arduino conventions.

## Notes for future agents
- This repository currently has no existing `.github/copilot-instructions.md` or `AGENTS.md`.
- If the user asks for more detailed development workflow or testing, consult and extend `README.md` and `platformio.ini`.
