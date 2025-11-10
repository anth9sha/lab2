#include <iostream>
#include <sstream>
#include <string>
#include "Array.h"
#include "List.h"

using namespace std;

int getMinrun(int n) {
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

int gallopLeft(int key, Array& arr, int base, int len) {
    int ofs = 1;
    int lastOfs = 0;
    while (ofs < len && arr[base + ofs] < key) {
        lastOfs = ofs;
        ofs = (ofs << 1) + 1;
        if (ofs > len)
            ofs = len;
    }
    int lo = lastOfs;
    int hi = ofs;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (arr[base + mid] < key)
            lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int gallopRight(int key, Array& arr, int base, int len) {
    int ofs = 1;
    int lastOfs = 0;
    while (ofs < len && key >= arr[base + ofs]) {
        lastOfs = ofs;
        ofs = (ofs << 1) + 1;
        if (ofs > len)
            ofs = len;
    }
    int lo = lastOfs;
    int hi = ofs;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (key >= arr[base + mid])
            lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

Array mergeRuns(Array& left, Array& right) {
    int n1 = left.getSize();
    int n2 = right.getSize();
    Array merged(n1 + n2);

    int i = 0, j = 0, k = 0;
    int minGallop = 7;
    int streakL = 0, streakR = 0;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            merged[k++] = left[i++];
            streakL++; streakR = 0;
        } else {
            merged[k++] = right[j++];
            streakR++; streakL = 0;
        }

        if (streakL >= minGallop) {
            int key = right[j];
            int pos = gallopLeft(key, left, i, n1 - i);
            int end = i + pos;
            while (i < end) {
                merged[k++] = left[i++];
            }
            streakL = streakR = 0;
        }
        else if (streakR >= minGallop) {
            int key = left[i];
            int pos = gallopRight(key, right, j, n2 - j);
            int end = j + pos;
            while (j < end) {
                merged[k++] = right[j++];
            }
            streakL = streakR = 0;
        }
    }

    while (i < n1)
        merged[k++] = left[i++];
    while (j < n2)
        merged[k++] = right[j++];

    return merged;
}

Array Run(Array& arr, int minrun) {
    Array run;
    if (arr.getSize() == 0) return run;

    bool needReverse = false;
    if (arr.getSize() > 1 && arr[0] > arr[1]) needReverse = true;

    int i = 0;
    run.resize(1);
    run[0] = arr[0];

    while (i + 1 < arr.getSize() && ((arr[i] <= arr[i + 1]) != needReverse)) {
        i++;
        run.resize(run.getSize() + 1);
        run[run.getSize() - 1] = arr[i];
    }

    if (needReverse) {
        for (int l = 0, r = run.getSize() - 1; l < r; l++, r--) {
            int tmp = run[l]; run[l] = run[r]; run[r] = tmp;
        }
    }

    int runSize = run.getSize();
    int targetSize;
    if (minrun < arr.getSize() + runSize)
        targetSize = minrun;
    else
        targetSize = (runSize + arr.getSize());

    while (run.getSize() < targetSize && arr.getSize() > 0) {
        run.resize(run.getSize() + 1);
        run[run.getSize() - 1] = arr[0];

        for (int j = 1; j < arr.getSize(); j++)
            arr[j - 1] = arr[j];
        arr.resize(arr.getSize() - 1);
    }

    for (int j = 1; j < run.getSize(); j++) {
        int key = run[j];
        int k = j - 1;
        while (k >= 0 && run[k] > key) {
            run[k + 1] = run[k];
            k--;
        }
        run[k + 1] = key;
    }

    return run;
}
void invariant(List& runs, Array& newRun) {
    runs.pushBack(newRun);
    while (runs.size() >= 3) {
        int n = runs.size();
        int lenA = runs.get(n-1).getSize();
        int lenB = runs.get(n-2).getSize();
        int lenC = runs.get(n-3).getSize();
        if (lenA <= lenB + lenC) {
            Array right = runs.peek(); runs.popBack();
            Array left = runs.peek(); runs.popBack();
            Array merged = mergeRuns(left, right);
            runs.pushBack(merged);
        } else if (lenB <= lenC) {
            Array right = runs.get(n-2); runs.popBack();
            Array left = runs.get(n-3); runs.popBack();
            Array merged = mergeRuns(left, right);
            runs.pushBack(merged);
        } else {
            break;
        }
    }
}

void timsort(Array& arr) {
    int minrun = getMinrun(arr.getSize());
    List runs;
    while (arr.getSize() > 0) {
        Array run = Run(arr, minrun);
        if (run.getSize() > 0)
            invariant(runs, run);
    }
    while (runs.size() > 1) {
        Array right = runs.peek();
        runs.popBack();
        Array left = runs.peek();
        runs.popBack();
        Array merged = mergeRuns(left, right);
        invariant(runs, merged);
    }
    if (!runs.empty()) {
        Array sorted = runs.peek();
        arr.resize(sorted.getSize());
        for (int i = 0; i < sorted.getSize(); i++) arr[i] = sorted[i];
    }
}

int main() {
    int repeat = 1;

    while (repeat == 1) {
        cout << "Enter the elements of the array separated by spaces:";

        string input;
        getline(cin, input);
        stringstream ss(input);

        Array arr;
        int val;
        while (ss >> val) {
            arr.resize(arr.getSize() + 1);
            arr[arr.getSize() - 1] = val;
        }

        timsort(arr);

        cout << "\nSorted array:\n";
        for (int i = 0; i < arr.getSize(); i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";

        cout << "\nAnother one? (1 = yes, any other = no): ";
        string answer;
        getline(cin, answer);
        if (answer == "1") {
            repeat = 1;
        } else {
            repeat = 0;
        }
        cout << "\n";
    }
    return 0;
}