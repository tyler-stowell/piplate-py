# setup.py
from distutils.core import setup, Extension

def main():
	setup(	name="plateio",
		version="1.0.0",
		description="Code to interface with driver for pi plates",
		author="Tyler Stowell",
		author_email="tyler@harschsystems.com",
		ext_modules=[Extension("plateio", ["plateio.c"])])

if __name__ == "__main__":
	main()
