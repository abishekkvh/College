import java.util.*;

public class MinimumPath {
    public int minimumEffortPath(int[][] heights) {
        int rows = heights.length;
        int cols = heights[0].length;

        // Track the minimum effort required to reach each cell
        int[][] efforts = new int[rows][cols];
        for (int[] row : efforts) {
            Arrays.fill(row, Integer.MAX_VALUE);
        }

        // Priority Queue stores: [effort, row, col]
        PriorityQueue<int[]> minHeap = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));

        // Base case: Start at top-left cell
        efforts[0][0] = 0;
        minHeap.offer(new int[] { 0, 0, 0 });

        // Direction vectors for moving: up, down, left, right
        int[][] directions = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

        while (!minHeap.isEmpty()) {
            int[] current = minHeap.poll();
            int currentEffort = current[0];
            int r = current[1];
            int c = current[2];

            // Early exit: First time reaching bottom-right cell is guaranteed minimal
            if (r == rows - 1 && c == cols - 1) {
                return currentEffort;
            }

            // Skip processing if a better effort path to this cell has already been found
            if (currentEffort > efforts[r][c]) {
                continue;
            }

            // Explore 4-directional neighbors
            for (int[] dir : directions) {
                int nextR = r + dir[0];
                int nextC = c + dir[1];

                // Ensure boundary limits are respected
                if (nextR >= 0 && nextR < rows && nextC >= 0 && nextC < cols) {
                    // Effort required to transition into the next cell
                    int edgeEffort = Math.abs(heights[r][c] - heights[nextR][nextC]);
                    // Total path effort is the maximum bottleneck along the route
                    int routeEffort = Math.max(currentEffort, edgeEffort);

                    // If this route offers a smaller effort bottleneck, update and queue it
                    if (routeEffort < efforts[nextR][nextC]) {
                        efforts[nextR][nextC] = routeEffort;
                        minHeap.offer(new int[] { routeEffort, nextR, nextC });
                    }
                }
            }
        }

        return 0;
    }

    public static void main(String[] args) {
        MinimumPath obj = new MinimumPath();
        int[][] heights = {{1,2,2},{3,8,2},{5,3,5}};
        System.out.println("Minimum Effort Path: " + obj.minimumEffortPath(heights));
    }
}
