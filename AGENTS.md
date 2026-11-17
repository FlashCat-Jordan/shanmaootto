# AGENTS.md

## Project

This repository is the standalone **闪猫1号 / Shanmao 1 Otto camera** firmware. It was extracted from `78/xiaozhi-esp32` and only keeps the `otto-robot` board plus the shared board helpers and core application code.

- Target: ESP32-S3
- Board: `main/boards/otto-robot/`
- Build entry: `scripts/build.py otto-robot`
- Project config: `main/Kconfig.projbuild` (only `BOARD_TYPE_OTTO_ROBOT`)
- Board selection: `main/CMakeLists.txt` (fixed to `otto-robot`)

Do not add other board directories or re-introduce the upstream multi-board selection chain.

## Architecture

- `main/application.*`: application main loop, networking/activation, state machine.
- `main/mcp_server.*`: device-side MCP tools.
- `main/audio/`: AFE, wake word, codecs, audio service.
- `main/display/`: LVGL display, emoji, fonts.
- `main/protocols/`: WebSocket and MQTT/UDP transports.
- `main/boards/common/`: board interfaces, camera, Wi-Fi, battery helpers.
- `main/boards/otto-robot/`: pins, camera, six servos, display, audio, WebSocket control.
- `main/CMakeLists.txt`: source list, Otto fonts/emoji, language selection.
- `scripts/build.py`: canonical build entry (board/config.json → sdkconfig → IDF build).

## Commands

```bash
source ~/esp/esp-idf-v6.0.1/export.sh

python3 scripts/build.py otto-robot \
  --name otto-robot \
  --language zh-CN \
  --wake-word wn9_nihaoxiaozhi_tts
```

Useful:

```bash
python3 scripts/build.py --list-boards
idf.py build
idf.py size
```

## Rules

- Keep the project Otto-only. Do not add unrelated boards.
- ESP-IDF 6.0.1+ is required; IDF 5.x is not supported.
- Preserve the board identity `otto-robot`; OTA compatibility depends on it.
- Keep `main/boards/otto-robot/config.h` as the single pin source of truth.
- Treat camera, display, audio and battery as optional where the code already does.
- Do not change servo limits without hardware confirmation:
  - mouth: 45°–60° only;
  - neck: 45°–180°, 135° forward;
  - legs/feet: normal near 75°–105°.
- Do not flip camera hmirror/vflip and preview rotation at the same time.
- A build is not hardware validation. Explicitly state what still needs a real robot.
- Do not rewrite unrelated files or mass-format the tree.
- Keep generated output (`build/`, `managed_components/`, `sdkconfig`, `releases/`) out of commits.
- Format touched C/C++ with the repository `.clang-format`.
