from pathlib import Path
from pytmx import TiledObjectGroup, TiledObject
from pytmx.util_pygame import load_pygame
import struct
import pygame

MAPS_PATH = Path("../src/resources/data/maps/")

def main() -> None:
    d = pygame.display.set_mode((50, 50))

    for file in MAPS_PATH.iterdir():
        if file.suffix == ".tmx":
            tiled = load_pygame(file)
            output = open(MAPS_PATH / f"{file.stem}.bin", "wb")
            tmp = open(f"{file.stem}.txt", "w")
            tmp.write(f"{tiled.width * tiled.tilewidth} {tiled.height * tiled.tilewidth}\n")
            output.write(struct.pack('i', tiled.width * tiled.tilewidth))
            output.write(struct.pack('i', tiled.height * tiled.tilewidth))
            tiledgroups: list[TiledObjectGroup] = [x for x in tiled.layers]
            for tiledgroup in tiledgroups:
                if not isinstance(tiledgroup, TiledObjectGroup):
                    continue
                objs: list[TiledObject] = [x for x in tiledgroup]
                tmp.write(f"{tiledgroup.properties['group-id']} {len(objs)}\n")
                output.write(struct.pack('i', tiledgroup.properties['group-id']))
                output.write(struct.pack('i', len(objs)))
                for obj in objs:
                    tmp.write(f"{obj.x} {obj.y} {obj.width} {obj.height} {obj.properties.get('obj-id', -1)}")
                    output.write(struct.pack('f', obj.x))
                    output.write(struct.pack('f', obj.y))
                    output.write(struct.pack('f', obj.width))
                    output.write(struct.pack('f', obj.height))
                    output.write(struct.pack('i', obj.properties.get('obj-id', -1)))
                    if (tiledgroup.name == "Coast"):
                        output.write(struct.pack('i', obj.properties.get('terrain')))
                        output.write(struct.pack('i', obj.properties.get('n')))
                        tmp.write(f" {obj.properties.get('terrain')} {obj.properties.get('n')}")                        
                    if (obj.properties.get("source") and tiledgroup.name != "Coast"):
                        imagepath = "./resources/graphics" + obj.properties["source"].split("graphics")[1] + '\0'
                        tmp.write(f" {imagepath}\n")
                        output.write(bytes(imagepath, "ASCII"))
                    else:
                        tmp.write('\n')

            output.close()
        
if __name__ == "__main__":
    main()