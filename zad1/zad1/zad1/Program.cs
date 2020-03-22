using GeneticSharp.Domain;
using GeneticSharp.Domain.Chromosomes;
using GeneticSharp.Domain.Crossovers;
using GeneticSharp.Domain.Fitnesses;
using GeneticSharp.Domain.Mutations;
using GeneticSharp.Domain.Populations;
using GeneticSharp.Domain.Selections;
using GeneticSharp.Domain.Terminations;
using org.mariuszgromada.math.mxparser;
using System;

namespace zad1
{
    class Program
    {
        static void Main(string[] args)
        {
            //var selection = Selection(1);
            //var crossover = Crossover(1, 0.5f);
            //var mutation = Mutation(1);
            //var termination = Termination(1, 100);
            Menu(out string[] names,
                 out string expression,
                 out ISelection selection,
                 out ICrossover crossover,
                 out IMutation mutation,
                 out ITermination termination);

            var chromosome = new FloatingPointChromosome(
                new double[2 * 2].Fill(Int32.MinValue),
                new double[2 * 2].Fill(Int32.MaxValue),
                new int[2 * 2].Fill(2 * 8 * sizeof(Int32)),
                new int[2 * 2].Fill(0));
            var population = new Population(50, 100, chromosome);
            var fitness = new FuncFitness(genotype =>
            {
                var fc = genotype as FloatingPointChromosome;

                var phenotype = fc.ToFloatingPoints();
                var x1 = phenotype[0];
                var y1 = phenotype[1];
                var x2 = phenotype[2];
                var y2 = phenotype[3];

                return Math.Sqrt(Math.Pow(x2 - x1, 2) + Math.Pow(y2 - y1, 2));
            });

            var geneticAlgorithm = new GeneticAlgorithm(population, fitness, selection, crossover, mutation)
            {
                Termination = termination
            };

            var latestFitness = 0.0;
            geneticAlgorithm.GenerationRan += (sender, e) =>
            {
                var bestChromosome = geneticAlgorithm.BestChromosome as FloatingPointChromosome;
                var bestFitness = bestChromosome.Fitness.Value;

                if (bestFitness != latestFitness)
                {
                    latestFitness = bestFitness;
                    var phenotype = bestChromosome.ToFloatingPoints();

                    Console.WriteLine(
                        "Generation {0, 3}:  ({1, 3}, {2, 3}),  ({3, 3}, {4, 3})\t= {5}",
                        geneticAlgorithm.GenerationsNumber,
                        phenotype[0],
                        phenotype[1],
                        phenotype[2],
                        phenotype[3],
                        bestFitness);
                }
            };
            geneticAlgorithm.Start();

            Console.ReadKey();
        }

        private static void Menu(
            out string[] names, out string expression,
            out ISelection selection, out ICrossover crossover,
            out IMutation mutation, out ITermination termination)
        {
            Console.Clear();
            Console.Write("Enter variable names separated by space:\t");
            names = Console.ReadLine().Split(' ');

            Console.WriteLine("\nEnter your expression:");
            expression = Console.ReadLine();

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
                    continue;
                }
            } while (!(1 <= selection_n && selection_n <= 4));
            selection = Selection(selection_n);

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
                    continue;
                }
            } while (!(1 <= crossover_n && crossover_n <= 7));
            crossover = Crossover(crossover_n, 0.5f);

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
                    continue;
                }
            } while (!(1 <= mutation_n && mutation_n <= 4));
            mutation = Mutation(mutation_n);

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
                    continue;
                }
            } while (!(1 <= termination_n && termination_n <= 4));
            termination = Termination(termination_n, 100);

            Console.Clear();
        }

        private static ISelection Selection(int n, object x = null, object y = null)
        {
            switch (n)
            {
                case 1:
                    return new EliteSelection();
                case 2:
                    return new RouletteWheelSelection();
                case 3:
                    return new StochasticUniversalSamplingSelection();
                case 4:
                    if (x is int)
                        if (y is bool)
                            return new TournamentSelection((int)x, (bool)y);
                        else
                            return new TournamentSelection((int)x);
                    else
                        return new TournamentSelection();
                default:
                    throw new ArgumentException();
            }
        }

        private static ICrossover Crossover(int n, object x = null) // TODO: check compatibility
        {
            switch (n)
            {
                case 1:
                    if (x is float)
                        return new UniformCrossover((float)x);
                    else
                        return new UniformCrossover();
                case 2:
                    return new CutAndSpliceCrossover();
                case 3:
                    return new CycleCrossover();
                case 4:
                    if (x is int)
                        return new OnePointCrossover((int)x);
                    else
                        return new OnePointCrossover();
                case 5:
                    return new PartiallyMappedCrossover();
                case 6:
                    return new PositionBasedCrossover();
                case 7:
                    return new ThreeParentCrossover();
                    //return new OrderedCrossover();
                    //return new OrderBasedCrossover();
                default:
                    throw new ArgumentException();
            }
        }

        private static IMutation Mutation(int n, object x = null)
        {
            switch (n)
            {
                case 1:
                    return new FlipBitMutation();
                case 2:
                    return new ReverseSequenceMutation();
                case 3:
                    return new TworsMutation();
                case 4:
                    if (x is int[])
                        return new UniformMutation((int[])x);
                    else if (x is bool)
                        return new UniformMutation((bool)x);
                    else
                        return new UniformMutation();
                default:
                    throw new ArgumentException();
            }
        }

        private static ITermination Termination(int n, object x = null)
        {
            switch (n)
            {
                case 1:
                    if (x is int)
                        return new FitnessStagnationTermination((int)x);
                    else
                        return new FitnessStagnationTermination();
                case 2:
                    if (x is int)
                        return new GenerationNumberTermination((int)x);
                    else
                        return new GenerationNumberTermination();
                case 3:
                    if (x is TimeSpan)
                        return new TimeEvolvingTermination((TimeSpan)x);
                    else
                        return new TimeEvolvingTermination();
                case 4:
                    if (x is double)
                        return new FitnessThresholdTermination((double)x);
                    else
                        return new FitnessThresholdTermination();
                default:
                    throw new ArgumentException();
            }
        }
    }
}
