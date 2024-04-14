package main

import (
	"fmt"
	"math"
	"os"
)

func firstFragm(x float64) float64 {
	res := -math.Sqrt(-x*x-4*x) + 2
	if math.Abs(res) < 0.000001 {
		res = 0.0
	}
	return res
}

func secondFragm(x float64) float64 {
	res := 0.0
	return res
}

func thirdFragm(x float64) float64 {
	res := -x
	return res
}

func fourthFragm(x float64) float64 {
	res := math.Sqrt(-x*x+6*x-5) - 1
	if math.Abs(res) < 0.000001 {
		res = 0.0
	}
	return res
}

func main() {
	xStart := -4.0
	xEnd := 5.0
	dx := 0.5

	file, err := os.Create("test.txt")
	if err != nil {
		fmt.Println("При открытии файла произошла ошибка")
		return
	}
	defer file.Close()

	fmt.Fprintf(file, "%10s %10s\n", "x", "y")
	for x := xStart; x <= xEnd; x += dx {
		if math.Abs(x) < 0.000001 {
			x = 0.0
		}
		if x >= -4.0 && x < -2.0 {
			fmt.Fprintf(file, "%10.2f %10.2f\n", x, firstFragm(x))
		}
		if x >= -2.0 && x <= 0.0 {
			fmt.Fprintf(file, "%10.2f %10.2f\n", x, secondFragm(x))
		}
		if x > 0.0 && x < 3.0 {
			fmt.Fprintf(file, "%10.2f %10.2f\n", x, thirdFragm(x))
		}
		if x >= 3.0 && x <= 5.0 {
			fmt.Fprintf(file, "%10.2f %10.2f\n", x, fourthFragm(x))
		}
	}
}
