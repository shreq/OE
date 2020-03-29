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
            //var selection = Selection(1);
            //var crossover = Crossover(1, 0.5f);
            //var mutation = Mutation(1);
            //var termination = Termination(1, 100);
            ParameterSelection parameters = ConsoleParameterSelectionFactory.CreateSelection();

            var chromosome = new FloatingPointChromosome(
                new double[parameters.Names.Length].Fill(parameters.LowerBound),
                new double[parameters.Names.Length].Fill(parameters.UpperBound),
                new int[parameters.Names.Length].Fill(2 * 8 * Marshal.SizeOf(parameters.LowerBound)),
                new int[parameters.Names.Length].Fill(0));
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
                var bestChromosome = geneticAlgorithm.BestChromosome as FloatingPointChromosome;
                var bestFitness = bestChromosome.Fitness.Value;

                if (bestFitness != latestFitness)
                {
                    previouslyBestFitness = latestFitness;
                    latestFitness = bestFitness;
                    var phenotype = bestChromosome.ToFloatingPoints();

                    var coords = "";
                    for (int i = 0; i < parameters.Names.Length; i++)
                    {
                        coords += "\n  " + parameters.Names[i] + "\t" + phenotype[i];
                    }
                    Console.WriteLine(
                        "Generation " + geneticAlgorithm.GenerationsNumber + " : \tbest fitness = " + bestFitness + coords
                    );
                }
            };
            geneticAlgorithm.GenerationRan += (sender, e) =>
            {
                var bestFitness = geneticAlgorithm.BestChromosome.Fitness.Value;

                var epsilon = Math.Abs(0.9 * latestFitness);
                if (Math.Abs(bestFitness - previouslyBestFitness) < epsilon &&
                    geneticAlgorithm.Crossover is UniformCrossover)
                {
                    var mixProbability = (geneticAlgorithm.Crossover as UniformCrossover).MixProbability;
                    geneticAlgorithm.Crossover = ParameterParser.ParserCrossover(1, (float)(0.9 * mixProbability));
                    Console.WriteLine(epsilon + " :e\tp: " +
                        (geneticAlgorithm.Crossover as UniformCrossover).MixProbability);
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
