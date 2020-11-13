#!/usr/bin/env python3
import argparse


class Rectangle:
    def __init__(self, x, y, w, h):
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    def __repr__(self):
        return f'DRAW_RECTANGLE {self.x},{self.y},{self.w},{self.h}'

    @staticmethod
    def spawn(start, delta_x, delta_y, end_x, end_y):
        print(f'SET_WIDTH {end_x}')
        print(f'SET_HEIGHT {end_y}')
        for x in range(start.x, end_x, delta_x):
            for y in range(start.y, end_y, delta_y):
                r = Rectangle(x, y, start.w, start.h)
                print(str(r))
        print(f'RENDER output.bmp')


class Triangle:
    def __init__(self, x1, y1, x2, y2, x3, y3):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.x3 = x3
        self.y3 = y3

    def __repr__(self):
        return f'DRAW_RECTANGLE {self.x1},{self.y1},{self.x2},{self.y2},{self.x3},{self.y3}'


def _parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('pattern', type=str, choices=['squared'], help='shape pattern')
    parser.add_argument('--width', type=int, default=500, help='image width')
    parser.add_argument('--height', type=int, default=500, help='image height')
    parser.add_argument('--size', type=int, default=25, help='object size')
    return parser.parse_args()


def generate_inputs(pattern, width, height, size):
    if pattern == 'squared':
        Rectangle.spawn(Rectangle(int(size / 2), int(size / 2), size, size), 2 * size, 2 * size, width, height)


if __name__ == '__main__':
    args = _parse_args()
    generate_inputs(args.pattern, args.width, args.height, args.size)
