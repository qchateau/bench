import sys
import pandas as pd
import matplotlib.pyplot as plt


def main():
    print("Loading data")
    df = pd.read_csv(sys.stdin)
    df = df.apply(pd.to_numeric, errors="coerce")  # convert all columns to numeric

    # Columns
    all_cols = [
        "exp_double_fast_math",
        "exp_float",
        "exp_float_fast_math",
        "exp_fast_float",
        "exp_very_fast_float",
    ]

    # Compute relative errors
    for col in all_cols:
        df[f"{col}_rerr"] = (df[col] - df["exp_double"]) / df["exp_double"]

    # Determine rolling window size in samples for rolling max
    x_spacing = df["x"].iloc[1] - df["x"].iloc[0]  # assume uniform spacing
    width = 2.0  # desired window width in x units
    window_size = max(1, int(width / x_spacing))  # at least 1 sample

    # --- Single plot: Rolling max of |relative error| ---
    fig, ax = plt.subplots(figsize=(10, 6))
    fig.suptitle(
        "Exponential Function Rolling Max |Relative Error| (log₁₀ scale)", fontsize=16
    )

    for col in all_cols:
        rolling_max = (
            df[f"{col}_rerr"]
            .abs()
            .rolling(window=window_size, min_periods=window_size)
            .max()
        )
        ax.plot(df["x"], rolling_max, label=col)

    ax.set_xlabel("x")
    ax.set_ylabel(f"Rolling Max |Relative Error| (width={width})")
    ax.set_yscale("log")
    ax.legend(fontsize=8, loc="upper left")
    ax.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    plt.show()


if __name__ == "__main__":
    main()
