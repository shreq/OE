using GeneticSharp.Domain.Crossovers;
using GeneticSharp.Domain.Mutations;
using GeneticSharp.Domain.Selections;
using GeneticSharp.Domain.Terminations;
using System;

namespace zad1.selection
{
    public class ConsoleParameterSelectionFactory
    {
        public static ParameterSelection CreateSelection()
        {
            Console.Clear();

            string[] names = GetNames();
            string expression = GetExpression();
            var bounds = GetBounds();
            float upperBound = bounds.upper;
            float lowerBound = bounds.lower;
            bool adaptiveOn = isAdaptive();
            ISelection selection = GetSelection();
            ICrossover crossover = GetCrossover();
            IMutation mutation = GetMutation();
            ITermination termination = GetTermination();

            Console.Clear();

            return new ParameterSelection
            {
                Variables = names,
                Expression = expression,
                LowerBound = lowerBound,
                UpperBound = upperBound,
                AdaptiveOn = adaptiveOn,
                Selection = selection,
                Crossover = crossover,
                Mutation = mutation,
                Termination = termination
            };
        }

        private static bool isAdaptive()
        {
            int isAdaptive_n;

            do
            {
                Console.Clear();
                Console.WriteLine("Choose genetic algorithm variant" +
                    "\n[1] Simple" +
                    "\n[2] Adaptive");
                try
                {
                    isAdaptive_n = int.Parse(Console.ReadKey().KeyChar.ToString());
                }
                catch
                {
                    isAdaptive_n = -1;
                }
            } while (!(1 <= isAdaptive_n && isAdaptive_n <= 2));

            return false ? isAdaptive_n == 1 : true;
        }

        private static string[] GetNames()
        {
            Console.Write("Enter variable names separated by space:\t");
            return Console.ReadLine().Split(' ');
        }

        private static string GetExpression()
        {
            Console.WriteLine("\nEnter your expression:");
            return Console.ReadLine();
        }

        private static (float lower, float upper) GetBounds()
        {
            float lowerBound, upperBound;

            do
            {
                try
                {
                    Console.Write("\nEnter range:" +
                        "\nlower bound = ");
                    lowerBound = float.Parse(Console.ReadLine());
                    Console.Write("upper bound = ");
                    upperBound = float.Parse(Console.ReadLine());
                }
                catch
                {
                    lowerBound = 1;
                    upperBound = -1;
                }
            } while (!(lowerBound < upperBound &&
                       Int32.MinValue <= lowerBound && upperBound <= Int32.MaxValue));

            return (lower: lowerBound, upper: upperBound);
        }

        private static ISelection GetSelection()
        {
            int selection_n;

            do
            {
                Console.Clear();
                Console.WriteLine("Choose selection method" +
                    "\n[1] Elite" +
                    "\n[2] Roulette Wheel" +
                    "\n[3] Stochastic Universal Sampling" +
                    "\n[4] Tournament");
                try
                {
                    selection_n = int.Parse(Console.ReadKey().KeyChar.ToString());
                }
                catch
                {
                    selection_n = -1;
                }
            } while (!(1 <= selection_n && selection_n <= 4));

            return ParameterParser.ParseSelection(selection_n);
        }

        private static ICrossover GetCrossover()
        {
            int crossover_n;

            do
            {
                Console.Clear();
                Console.WriteLine("Choose crossover method:" +
                    "\n[1] Uniform" +
                    "\n[2] One Point" +
                    "\n[3] Partially Mapped" +
                    "\n[4] Postition Based" +
                    "\n[5] Three Parent");
                try
                {
                    crossover_n = int.Parse(Console.ReadKey().KeyChar.ToString());
                }
                catch
                {
                    crossover_n = -1;
                }
            } while (!(1 <= crossover_n && crossover_n <= 5));

            return ParameterParser.ParserCrossover(crossover_n, 0.5f);
        }

        private static IMutation GetMutation()
        {
            int mutation_n;

            do
            {
                Console.Clear();
                Console.WriteLine("Choose mutation method:" +
                    "\n[1] Flip Bit" +
                    "\n[2] Reverse Sequence" +
                    "\n[3] Twors" +
                    "\n[4] Uniform");
                try
                {
                    mutation_n = int.Parse(Console.ReadKey().KeyChar.ToString());
                }
                catch
                {
                    mutation_n = -1;
                }
            } while (!(1 <= mutation_n && mutation_n <= 4));

            return ParameterParser.ParseMutation(mutation_n);
        }

        private static ITermination GetTermination()
        {
            int termination_n;

            do
            {
                Console.Clear();
                Console.WriteLine("Choose termination method:" +
                    "\n[1] Fitness Stagnation" +
                    "\n[2] Generation Number" +
                    "\n[3] Time Evolving" +
                    "\n[4] Fitness Threshold");
                try
                {
                    termination_n = int.Parse(Console.ReadKey().KeyChar.ToString());
                }
                catch
                {
                    termination_n = -1;
                }
            } while (!(1 <= termination_n && termination_n <= 4));

            return ParameterParser.ParseTermination(termination_n, 100);
        }
    }
}
