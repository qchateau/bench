import re
import sys
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors


def main():
    text = sys.stdin.read()

    # Parse lines
    pattern = r"(BM_[\w/]+)\s+[\d\.]+ ns.*items_per_second=([\d\.]+)([MG])/s"
    data = []
    for match in re.finditer(pattern, text):
        name, value, unit = match.groups()
        value = float(value) * (1e3 if unit == "G" else 1.0)  # convert G/s → 1000 M/s
        bench, size = name.rsplit("/", 1)
        data.append((bench, int(size), value))

    df = pd.DataFrame(data, columns=["Benchmark", "Size", "Throughput_Mps"])

    # Compute throughput at maximum size for each benchmark
    max_vals = df.loc[df.groupby("Benchmark")["Size"].idxmax()].set_index("Benchmark")[
        "Throughput_Mps"
    ]

    # Create color mapping based on ranking
    cmap = plt.colormaps.get_cmap("turbo")  # rainbow-like colormap
    norm = mcolors.Normalize(vmin=max_vals.min(), vmax=max_vals.max())
    color_map = {bench: cmap(norm(val)) for bench, val in max_vals.items()}

    # Plot
    fig, ax = plt.subplots(figsize=(10, 6))
    lines = []
    for bench, subdf in df.groupby("Benchmark"):
        (line,) = ax.plot(
            subdf["Size"],
            subdf["Throughput_Mps"],
            label=bench,
            color=color_map[bench],
            alpha=0.8,
        )
        lines.append((bench, line))

    ax.set_xscale("log", base=2)
    ax.set_yscale("log", base=2)
    ax.set_xlabel("Input Size")
    ax.set_ylabel("Throughput (Million items/s)")
    ax.set_title("Benchmark Throughput vs Input Size")

    # Order legend by throughput at maximum size
    # Sort descending so highest throughput is on top
    sorted_lines = sorted(lines, key=lambda x: max_vals[x[0]], reverse=True)
    sorted_handles = [line for _, line in sorted_lines]
    sorted_labels = [bench for bench, _ in sorted_lines]

    ax.legend(
        sorted_handles,
        sorted_labels,
        bbox_to_anchor=(1.05, 1),
        loc="upper left",
        fontsize=8,
    )

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
