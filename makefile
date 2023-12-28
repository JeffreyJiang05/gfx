CC=g++
SRC_DIR=src/
INCLUDE_DIR=include/
BUILD_DIR=build/
IMAGE_DIR=img/
CPP_VER=c++20
OPTIMIZATION=-march=native -O3

FLAGS=-std=$(CPP_VER) $(OPTIMIZATION) -Wall -Werror -I$(INCLUDE_DIR)

ENGINE_DIR=$(SRC_DIR)engine/
TEST_DIR=$(SRC_DIR)test/
BUILD_TEST_DIR=$(BUILD_DIR)test/
BUILD_LIB_DIR=$(BUILD_DIR)lib/

SOURCES=$(shell find $(ENGINE_DIR) -name '*.cpp' -printf "%f\n" | sort -k 1nr)
OBJECTS=$(SOURCES:%.cpp=$(BUILD_LIB_DIR)%.o)

vec_test: $(BUILD_DIR)vec_test
	$(BUILD_DIR)vec_test
mat_test: $(BUILD_DIR)matrix_test
	$(BUILD_DIR)matrix_test
rflt_test: $(BUILD_DIR)rflt_test
	$(BUILD_DIR)rflt_test
pix_test: $(BUILD_DIR)pix_test
	$(BUILD_DIR)pix_test
gfx2d_test: $(BUILD_DIR)GFX2D_test
	$(BUILD_DIR)GFX2D_test
gfx2d_perf: $(BUILD_DIR)GFX2D_perf
	$(BUILD_DIR)GFX2D_perf
polygon_test: $(BUILD_DIR)polygon_test
	$(BUILD_DIR)polygon_test
curve_test: $(BUILD_DIR)curve_test
	$(BUILD_DIR)curve_test
antialias_test: $(BUILD_DIR)antialias_test
	$(BUILD_DIR)antialias_test
triangle_test: $(BUILD_DIR)triangle_test
	$(BUILD_DIR)triangle_test

$(BUILD_DIR)vec_test: $(BUILD_DIR) $(OBJECTS) $(BUILD_TEST_DIR)vec_test.o 
	$(CC) $(BUILD_TEST_DIR)vec_test.o $(OBJECTS) $(FLAGS) -o $(BUILD_DIR)vec_test
$(BUILD_DIR)matrix_test: $(BUILD_DIR) $(OBJECTS) $(BUILD_TEST_DIR)matrix_test.o 
	$(CC) $(BUILD_TEST_DIR)matrix_test.o $(OBJECTS) $(FLAGS) -o $(BUILD_DIR)matrix_test
$(BUILD_DIR)rflt_test: $(BUILD_DIR) $(OBJECTS) $(BUILD_TEST_DIR)rflt_test.o 
	$(CC) $(BUILD_TEST_DIR)rflt_test.o $(OBJECTS) $(FLAGS) -o $(BUILD_DIR)rflt_test
$(BUILD_DIR)pix_test: $(BUILD_DIR) $(OBJECTS) $(BUILD_TEST_DIR)pix_test.o 
	$(CC) $(BUILD_TEST_DIR)pix_test.o $(OBJECTS) $(FLAGS) -o $(BUILD_DIR)pix_test
$(BUILD_DIR)GFX2D_test: $(BUILD_DIR) $(IMAGE_DIR) $(OBJECTS) $(BUILD_TEST_DIR)GFX2D_test.o 
	$(CC) $(BUILD_TEST_DIR)GFX2D_test.o $(OBJECTS) $(FLAGS) -o $(BUILD_DIR)GFX2D_test
$(BUILD_DIR)GFX2D_perf: $(BUILD_DIR) $(IMAGE_DIR) $(OBJECTS) $(BUILD_TEST_DIR)GFX2D_perf.o 
	$(CC) $(BUILD_TEST_DIR)GFX2D_perf.o $(OBJECTS) $(FLAGS) -o $(BUILD_DIR)GFX2D_perf
$(BUILD_DIR)polygon_test: $(BUILD_DIR) $(IMAGE_DIR) $(OBJECTS) $(BUILD_TEST_DIR)polygon_test.o 
	$(CC) $(BUILD_TEST_DIR)polygon_test.o $(OBJECTS) $(FLAGS) -o $(BUILD_DIR)polygon_test
$(BUILD_DIR)curve_test: $(BUILD_DIR) $(IMAGE_DIR) $(OBJECTS) $(BUILD_TEST_DIR)curve_test.o 
	$(CC) $(BUILD_TEST_DIR)curve_test.o $(OBJECTS) $(FLAGS) -o $(BUILD_DIR)curve_test
$(BUILD_DIR)antialias_test: $(BUILD_DIR) $(IMAGE_DIR) $(OBJECTS) $(BUILD_TEST_DIR)antialias_test.o 
	$(CC) $(BUILD_TEST_DIR)antialias_test.o $(OBJECTS) $(FLAGS) -o $(BUILD_DIR)antialias_test
$(BUILD_DIR)triangle_test: $(BUILD_DIR) $(IMAGE_DIR) $(OBJECTS) $(BUILD_TEST_DIR)triangle_test.o 
	$(CC) $(BUILD_TEST_DIR)triangle_test.o $(OBJECTS) $(FLAGS) -o $(BUILD_DIR)triangle_test

$(BUILD_TEST_DIR)%.o: $(TEST_DIR)%.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_LIB_DIR)Pixel.o: $(ENGINE_DIR)gfx/base/Pixel.cpp $(INCLUDE_DIR)gfx/base/Pixel.hpp $(INCLUDE_DIR)gfx/base/Pixel.inl 
	$(CC) $(FLAGS) -c $< -o $@
$(BUILD_LIB_DIR)Image.o: $(ENGINE_DIR)gfx/base/Image.cpp $(INCLUDE_DIR)gfx/base/Image.hpp $(INCLUDE_DIR)gfx/base/Image.inl 
	$(CC) $(FLAGS) -c $< -o $@
$(BUILD_LIB_DIR)2DDraw.o: $(ENGINE_DIR)gfx/2D/2DDraw.cpp $(INCLUDE_DIR)gfx/2D/Draw.hpp $(INCLUDE_DIR)gfx/2D/Draw.inl
	$(CC) $(FLAGS) -c $< -o $@
$(BUILD_LIB_DIR)2DVertexList.o: $(ENGINE_DIR)gfx/2D/2DVertexList.cpp $(INCLUDE_DIR)gfx/2D/VertexList.hpp $(INCLUDE_DIR)gfx/2D/VertexList.inl
	$(CC) $(FLAGS) -c $< -o $@
$(BUILD_LIB_DIR)2DTransformation.o: $(ENGINE_DIR)gfx/2D/2DTransformation.cpp $(INCLUDE_DIR)gfx/2D/Transformation.hpp
	$(CC) $(FLAGS) -c $< -o $@
$(BUILD_LIB_DIR)2DConstruct.o: $(ENGINE_DIR)gfx/2D/2DConstruct.cpp $(INCLUDE_DIR)gfx/2D/Construct.hpp
	$(CC) $(FLAGS) -c $< -o $@
$(BUILD_LIB_DIR)2DVertexAdapter.o: $(ENGINE_DIR)gfx/2D/2DVertexAdapter.cpp $(INCLUDE_DIR)gfx/2D/VertexAdapter.hpp $(INCLUDE_DIR)gfx/2D/VertexAdapter.inl
	$(CC) $(FLAGS) -c $< -o $@
$(BUILD_LIB_DIR)%.o: $(ENGINE_DIR)lib/%.cpp
	$(CC) -std=$(CPP_VER) $(OPTIMIZATION) -I$(INCLUDE_DIR) -c $< -o $@


$(BUILD_DIR):
	mkdir $(BUILD_DIR)
	mkdir $(BUILD_TEST_DIR)
	mkdir $(BUILD_LIB_DIR)

$(IMAGE_DIR):
	mkdir $(IMAGE_DIR)

.PHONY: clean
clean:
	rm -rfv $(BUILD_DIR)

.PHONY: clean_images
clean_images:
	rm -rfv $(IMAGE_DIR)
