using GeneticSharp.Domain;
using GeneticSharp.Domain.Chromosomes;
using GeneticSharp.Domain.Crossovers;
using GeneticSharp.Domain.Fitnesses;
using GeneticSharp.Domain.Mutations;
using GeneticSharp.Domain.Populations;
using GeneticSharp.Domain.Selections;
using GeneticSharp.Domain.Terminations;
using System;

namespace zad1
{
    class Program
    {
        static void Main(string[] args)
        {
            float maxWidth = 998f;
            float maxHeight = 680f;

            var chromosome = new FloatingPointChromosome(
                new double[] { 0, 0, 0, 0 },
                new double[] { maxWidth, maxHeight, maxWidth, maxHeight },
                new int[] { 10, 10, 10, 10 },
                new int[] { 0, 0, 0, 0 });
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

            var selection = Selection(1);
            var crossover = Crossover(1, 0.5f);
            var mutation = Mutation(1);
            var termination = Termination(1, 100);

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
