all: debug optimization
		

debug:
		g++ -g Solution.cpp -o debug

optimization:
		g++ -O Solution.cpp -o optimized