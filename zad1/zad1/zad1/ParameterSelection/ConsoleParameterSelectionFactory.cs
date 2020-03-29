using GeneticSharp.Domain.Crossovers;
using GeneticSharp.Domain.Mutations;
using GeneticSharp.Domain.Selections;
using GeneticSharp.Domain.Terminations;
using System;
using System.Collections.Generic;
using System.Text;

namespace zad1.selection
{
    public class ConsoleParameterSelectionFactory
    {
        public static ParameterSelection createSelection()
        {
            Console.Clear();

            string[] names = getNames();
            string expression = getExpression();
            var bounds = getBounds();
            float upperBound = bounds.upper;
            float lowerBound = bounds.lower;
            ISelection selection = getSelection();
            ICrossover crossover = getCrossover();
            IMutation mutation = getMutation();
            ITermination termination = getTermination();

            Console.Clear();

            return new ParameterSelection
            {
                Names = names,
                Expression = expression,
                LowerBound = lowerBound,
                UpperBound = upperBound,
                Selection = selection,
                Crossover = crossover,
                Mutation = mutation,
                Termination = termination
            };
        }

        private static string[] getNames()
        {
            Console.Write("Enter variable names separated by space:\t");
            return Console.ReadLine().Split(' ');
        }

        private static string getExpression()
        {
            Console.WriteLine("\nEnter your expression:");
            return Console.ReadLine();
        }

        private static (float lower, float upper) getBounds()
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

        private static ISelection getSelection()
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
            return ParameterParser.parseSelection(selection_n);
        }

        private static ICrossover getCrossover()
        {
            int crossover_n;
            do
            {
                Console.Clear();
                Console.WriteLine("Choose crossover method:" +
                    "\n[1] Uniform" +
                    "\n[2] Cut and Splice" +
                    "\n[3] Cycle" +
                    "\n[4] One Point" +
                    "\n[5] Partially Mapped" +
                    "\n[6] Postition Based" +
                    "\n[7] Three Parent");
                try
                {
                    crossover_n = int.Parse(Console.ReadKey().KeyChar.ToString());
                }
                catch
                {
                    crossover_n = -1;
                }
            } while (!(1 <= crossover_n && crossover_n <= 7));
            return ParameterParser.parserCrossover(crossover_n, 0.5f);
        }

        private static IMutation getMutation()
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
            return ParameterParser.parseMutation(mutation_n);
        }

        private static ITermination getTermination()
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
            return ParameterParser.parseTermination(termination_n, 100);
        }
    }
}
