from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.build import can_run
import os

class MeenHwRecipe(ConanFile):
    name = "action"
    version = "0.0.1"
    package_type = "library"
    test_package_folder = "tests/conan_package_test"

    # Optional metadata
    license = "MIT"
    author = "Nicolas Beddows <nicolas.beddows@gmail.com>"
    url = "https://github.com/action-test"
    description = "Github actions test"
    topics = ("Github actions")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"gtest*:build_gmock": False, "shared": True, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt",\
        "LICENSE",\
        "README.md",\
        "include/*",\
        "source/*",\
        "tests/action_test/*"

    def requirements(self):
        self.requires("nlohmann_json/3.11.3")

    def build_requirements(self):
        self.test_requires("gtest/1.14.0")

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

        if self.settings.os == "Windows":
            self.folders.build = "output/build"
            self.folders.generators = "output/build/generators"

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["build_arch"] = self.settings.arch
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

        if can_run(self) and not self.conf.get("tools.build:skip_test", default=False):
            testsDir = os.path.join(self.source_folder, "artifacts", str(self.settings.build_type), str(self.settings.arch), self.cpp_info.bindirs[0])
            print("TD: ", testsDir)
            self.run(os.path.join(testsDir, "action_test"))

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = [self.name]
