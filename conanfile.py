from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

cpu_frequencies = [int(8_000_000 / prescale) for prescale in 
    [2 ** i for i in range(9)]]

class AvrCppRecipe(ConanFile):
    name = "avr_cpp"
    version = "0.1"
    package_type = "static-library"

    settings = "os", "compiler", "build_type", "arch"
    options = {"mcu": ['atmega168'], "f_cpu": cpu_frequencies}

    default_options = {"f_cpu": 1_000_000}

    exports_sources = "CMakeLists.txt", "src/*", "include/*", \
        "test/*", "avr_stub/*"

    def config_options(self):
        if not self.settings.arch == 'avr':
            del self.options.mcu

    def layout(self):
        cmake_layout(self)

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.23]")

    def requirements(self):
        self.requires("etl/20.38.4", transitive_headers=True)

        if not self.conf.get("tools.build:skip_test", default=False):
            self.test_requires("gtest/[~1.14]")

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        tc = CMakeToolchain(self)
        tc.preprocessor_definitions["F_CPU"] = self.options.f_cpu

        if self.settings.arch == "avr":
            tc.extra_cxxflags = [f"-mmcu={self.options.mcu}"]
            tc.preprocessor_definitions["ETL_NO_STL"] = True
            tc.preprocessor_definitions["ETL_NO_CPP_NAN_SUPPORT"] = True

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

        if not self.conf.get("tools.build:skip_test", default=False):
            cmake.ctest()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["avr_cpp"]
        self.cpp_info.defines = [f"F_CPU={self.options.f_cpu}"]

        if self.settings.arch == "avr":
            self.cpp_info.cxxflags = [f"-mmcu={self.options.mcu}"]
            self.cpp_info.exelinkflags = [f"-mmcu={self.options.mcu}"]
            self.cpp_info.defines += ["ETL_NO_STL", "ETL_NO_CPP_NAN_SUPPORT"]