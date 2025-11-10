import sys
import pandas as pd
import matplotlib.pyplot as plt


def main():
    print("Loading data")
    df = pd.read_csv(sys.stdin)
    df = df.apply(pd.to_numeric, errors="coerce")  # convert all columns to numeric

    # Columns
    float_cols = ["exp_fast_float", "exp_very_fast_float"]
    double_cols = ["exp_float", "exp_fast_double", "exp_very_fast_double"]
    all_cols = float_cols + double_cols

    # Compute relative errors
    for col in float_cols:
        df[f"{col}_rerr"] = (df[col] - df["exp_float"]) / df["exp_float"]
    for col in double_cols:
        df[f"{col}_rerr"] = (df[col] - df["exp_double"]) / df["exp_double"]

    # Determine rolling window size in samples for rolling max
    x_spacing = df["x_float"].iloc[1] - df["x_float"].iloc[0]  # uniform spacing
    width = 2.0  # desired window width in x units
    window_size = max(1, int(width / x_spacing))  # at least 1 sample

    # Create figure with three subplots
    fig, axes = plt.subplots(3, 1, figsize=(10, 15))
    fig.suptitle("Exponential Function Relative Errors", fontsize=16)

    # --- Top plot: rolling max of absolute relative error ---
    for col in all_cols:
        rolling_max = (
            df[f"{col}_rerr"]
            .abs()
            .rolling(window=window_size, min_periods=window_size)
            .max()
        )
        axes[0].plot(df["x_float"], rolling_max, label=col)
    axes[0].set_xlabel("x")
    axes[0].set_ylabel(f"Rolling Max |Relative Error| (width={width})")
    axes[0].legend(
        bbox_to_anchor=(1.05, 1),
        loc="upper left",
        fontsize=8,
        borderaxespad=0,
        frameon=True,
    )

    # --- Middle plot: original raw relative error ---
    for col in all_cols:
        axes[1].plot(df["x_float"], df[f"{col}_rerr"], label=col)
    axes[1].set_xlabel("x")
    axes[1].set_ylabel("Relative Error")
    axes[1].legend(
        bbox_to_anchor=(1.05, 1),
        loc="upper left",
        fontsize=8,
        borderaxespad=0,
        frameon=True,
    )

    # --- Bottom plot: zoomed-in x ∈ [0, 2] ---
    for col in all_cols:
        axes[2].plot(df["x_float"], df[f"{col}_rerr"], label=col)
    axes[2].set_xlim(0, 2)
    axes[2].set_xlabel("x")
    axes[2].set_ylabel("Relative Error")
    axes[2].legend(
        bbox_to_anchor=(1.05, 1),
        loc="upper left",
        fontsize=8,
        borderaxespad=0,
        frameon=True,
    )

    plt.tight_layout(rect=[0, 0.03, 0.85, 0.95])
    plt.show()


if __name__ == "__main__":
    main()
