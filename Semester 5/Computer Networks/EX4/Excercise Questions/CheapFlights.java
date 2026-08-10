import java.util.Arrays;

public class CheapFlights {
    public int findCheapestPrice(int n, int[][] flights, int src, int dst, int k) {
        // Track the minimum cost to reach each city
        int[] prices = new int[n];
        Arrays.fill(prices, Integer.MAX_VALUE);
        prices[src] = 0;

        // Perform at most K + 1 iterations (K stops means at most K + 1 flights)
        for (int i = 0; i <= k; i++) {
            // Create a copy to prevent using updated distances from the current iteration
            int[] tempPrices = Arrays.copyOf(prices, n);

            for (int[] flight : flights) {
                int from = flight[0];
                int to = flight[1];
                int price = flight[2];

                // If the starting city of this flight is reachable
                if (prices[from] != Integer.MAX_VALUE) {
                    // Check if taking this flight provides a cheaper option to reach 'to'
                    if (prices[from] + price < tempPrices[to]) {
                        tempPrices[to] = prices[from] + price;
                    }
                }
            }
            // Update the global prices array for the next step iteration
            prices = tempPrices;
        }

        // Return the final price if reachable, otherwise -1
        return prices[dst] == Integer.MAX_VALUE ? -1 : prices[dst];
    }

    public static void main(String[] args) {
        CheapFlights obj = new CheapFlights();
        int n = 4;
        int[][] flights = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
        int src = 0, dst = 3, k = 1;
        System.out.println("Cheapest Price: " + obj.findCheapestPrice(n, flights, src, dst, k));
    }
}
