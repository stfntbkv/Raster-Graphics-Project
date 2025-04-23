# Raster Image Editor

A raster graphics editor developed for a university project.

Supports **PPM, PGM, and PBM** image formats and allows multiple images to be managed through user sessions. Each session supports transformations, undo functionality, and exporting images after processing.

## Features

- Load and edit multiple images in a session
- Apply transformations:
  - grayscale
  - monochrome
  - negative
  - rotate left/right
- Undo last transformation
- Save all images in session or export individually
- Session switching and info view
- Create horizontal or vertical image collages (if types and dimensions match)

## Example Commands

```
> load image1.ppm
> add image2.pgm
> grayscale
> rotate left
> session info
> save
```
