from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMake, cmake_layout

class ExamplesRecipe(ConanFile):
    name = "examples"
    version = "0.1"
    package_type = "application"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def validate(self):
        if self.settings.arch != "avr":
            raise ConanInvalidConfiguration("Architecture is not AVR")

    def configure(self):
        self.options["avr_cpp/*"].mcu = 'atmega168'
        self.options["avr_cpp/*"].f_cpu = 1_000_000

    def layout(self):
        cmake_layout(self)

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.23]")

    def requirements(self):
        self.requires("avr_cpp/[>=0.1]")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
