/*
Argument 1 : Original price
Argument 2 : Discount Percentage

Return Final Price

Note : Answer should be rounded to 2 decimal places

Input : 100 75
Output : 25
*/

import java.util.Scanner;
import java.text.DecimalFormat;
public class FindTheDiscount
{
    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);

        int originalPrice = sc.nextInt();
        int discountPercentage = sc.nextInt();

        double finalPrice = originalPrice - (originalPrice * discountPercentage / 100.0);

        DecimalFormat df = new DecimalFormat("0.##");        
        System.out.println(df.format(finalPrice));
        sc.close();
    }
}