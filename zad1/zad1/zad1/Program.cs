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
using System.Runtime.InteropServices;
using zad1.EventHandlers;
using zad1.selection;

namespace zad1
{
    class Program
    {
        static void Main(string[] args)
        {
            const int NUMBER_OF_BITS = 2 * 8 * sizeof(float);

            ParameterSelection parameters = ConsoleParameterSelectionFactory.CreateSelection();

            var chromosome = new FloatingPointChromosome(
                new double[parameters.Names.Length].Fill(parameters.LowerBound),
                new double[parameters.Names.Length].Fill(parameters.UpperBound),
                new int[parameters.Names.Length].Fill(NUMBER_OF_BITS),
                new int[parameters.Names.Length].Fill(0)
            );
            var population = new Population(50, 100, chromosome);
            var fitness = new FunctionMinimumFitness()
            {
                FunctionVariables = parameters.Names,
                Expression = parameters.Expression
            };

            var geneticAlgorithm = new GeneticAlgorithm(population,
                                                        fitness,
                                                        parameters.Selection,
                                                        parameters.Crossover,
                                                        parameters.Mutation)
            {
                Termination = parameters.Termination
            };

            geneticAlgorithm.GenerationRan += new ConsoleLogEventHandler(parameters.Names).Handle;

            var latestFitness = 0.0;
            var previouslyBestFitness = 0.0;

            geneticAlgorithm.GenerationRan += (sender, e) =>
            {
                var bestFitness = geneticAlgorithm.BestChromosome.Fitness.Value;

                var epsilon = Math.Abs(0.9 * bestFitness);
                if (Math.Abs(bestFitness - previouslyBestFitness) < epsilon)
                {
                    if (geneticAlgorithm.Crossover is UniformCrossover)
                    {
                        var mixProbability = (geneticAlgorithm.Crossover as UniformCrossover).MixProbability;
                        geneticAlgorithm.Crossover = ParameterParser.ParserCrossover(1, (float)(0.9 * mixProbability));
                    }

                    if (geneticAlgorithm.Mutation is CustomUniformMutation)
                    {
                        geneticAlgorithm.Mutation = (geneticAlgorithm.Mutation as CustomUniformMutation).GenerateAdaptedMutation();
                    }

                }
            };

            geneticAlgorithm.Start();

            var latestCoords = "";
            var latestPhenotype = (geneticAlgorithm.BestChromosome as FloatingPointChromosome).ToFloatingPoints();
            for (int i = 0; i < parameters.Names.Length; i++)
            {
                latestCoords += "\n  " + parameters.Names[i] + "\t" + latestPhenotype[i];
            }
            Console.WriteLine("\n\n- - - Final result: - - -" +
                "\nGeneration " + geneticAlgorithm.GenerationsNumber + " : \tfitness = " + latestFitness +
                latestCoords + "\n\n  f(" + String.Join(", ", parameters.Names) + ") = " + (-latestFitness));

            Console.ReadKey();
        }
    }
}
