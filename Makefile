RTWeekend: clean
	clang++ -g -O0 code/main.cpp -o RTWeekend.out -lX11
run: RTWeekend
	./RTWeekend.out > image.ppm
clean:
	rm RTWeekend.out
clean_image:
	rm image.ppm