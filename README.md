# random_noise

A Qt/C++ desktop application that fetches a random playlist from Spotify and opens it for playback.

## Features

- Fetches Spotify categories and playlists via [Every noise](https://everynoise.com)
- Randomly selects a track/playlist and opens it in Spotify
- Minimal UI built with QML

## Project Structure

| File | Description |
|------|-------------|
| `main.cpp` | Application entry point |
| `Main.qml` | Main UI layout |
| `categoriesdownloader.*` | Fetches Spotify categories |
| `trackdownloader.*` | Fetches tracks for a given playlist |
| `trackselector.*` | Randomly selects a track |
| `randomnoise.*` | Core logic coordinating the flow |
| `randomnoiseelement.h` | Data model for a noise element |


## License
This project is licensed under the MIT License.
