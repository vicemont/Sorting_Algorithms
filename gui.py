
import tkinter as tk
from tkinter import ttk
import subprocess
from pathlib import Path

folder = Path(__file__).resolve().parent.parent

def run_algorithm():
    algorithm = algorithm_choice.get()
    size = size_choice.get()

    if not algorithm or not size:
        result_label.config(text="Please select an algorithm and size.")
        return

    try:
        result = subprocess.run(
    [str(Path(__file__).resolve().parent / "SortingBackend"), algorithm, size],
    cwd=project_folder,
    capture_output=True,
    text=True
)

        if result.returncode == 0:
            result_label.config(text=result.stdout)
        else:
            result_label.config(text=result.stderr or result.stdout)

    except Exception as error:
        result_label.config(text=f"Error: {error}")


# Create window
window = tk.Tk()
window.title("Sorting Algorithm Benchmark")
window.geometry("450x350")
window.resizable(False, False)

# Heading
heading = tk.Label(
    window,
    text="Sorting Algorithm Benchmark",
    font=("Arial", 18, "bold")
)
heading.pack(pady=20)

# Algorithm selection
tk.Label(window, text="Select Sorting Algorithm:").pack()

algorithm_choice = ttk.Combobox(
    window,
    values=[
        "Heap Sort",
        "Quick Sort",
        "Median-of-Three Quick Sort",
        "Merge Sort",
        "Insertion Sort",
        "Selection Sort",
        "Bubble Sort"
    ],
    state="readonly",
    width=35
)
algorithm_choice.pack(pady=8)
algorithm_choice.current(0)

# Input size selection
tk.Label(window, text="Select Input Size:").pack(pady=(10, 0))

size_choice = ttk.Combobox(
    window,
    values=["100", "500", "1000", "2000"],
    state="readonly",
    width=35
)
size_choice.pack(pady=8)
size_choice.current(0)

# Run button
run_button = tk.Button(
    window,
    text="Run Algorithm",
    command=run_algorithm,
    font=("Arial", 11, "bold"),
    bg="lightblue",
    width=20
)
run_button.pack(pady=15)

# Results
result_label = tk.Label(
    window,
    text="Results will appear here.",
    font=("Arial", 10),
    justify="center",
    wraplength=400
)
result_label.pack(pady=10)

window.mainloop()
