int main() {
    int Score = 0;

    int a = 5;
    if (a == 5) {
        Score++; // 1
    }

    int b = 4;
    if (b == 5) {
        return 0; // Fail
    } else {
        Score++; // 2
    }

    int c = 5, d = 10;
    if (c < d) {
        if (d == 10) {
            Score++; // 3
        }
    }

    int e = 0;
    while (e < 5) {
        e++;
    }
    if (e == 5) {
        Score++; // 4
    }

    int f = 0;
    while (f < 10) {
        f++;
        if (f == 5) break;
    }
    if (f == 5) {
        Score++; // 5
    }

    int g = 0, sum = 0;
    while (g < 5) {
        g++;
        if (g % 2 == 0) continue;
        sum += g;
    }
    if (sum == 9) { // 1+3+5
        Score++; // 6
    }

    printf("Test Score: %d/6\n", Score);
    return Score == 6 ? 1 : 0; // Pass if 6/6
}

// Failing with error "Invalid operator Type in ASTExpr"