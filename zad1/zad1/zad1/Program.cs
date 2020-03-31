using GeneticSharp.Domain;
using GeneticSharp.Domain.Chromosomes;
using GeneticSharp.Domain.Crossovers;
using GeneticSharp.Domain.Populations;
using System;
using System.IO;
using zad1.EventHandlers;
using zad1.selection;

namespace zad1
{
    class Program
    {
        static void Main(string[] _)
        {
            const int NUMBER_OF_BITS = 2 * 8 * sizeof(float);

            ParameterSelection parameters = ConsoleParameterSelectionFactory.CreateTestSelection();

            var chromosome = new FloatingPointChromosome(
                new double[parameters.Variables.Length].Fill(parameters.LowerBound),
                new double[parameters.Variables.Length].Fill(parameters.UpperBound),
                new int[parameters.Variables.Length].Fill(NUMBER_OF_BITS),
                new int[parameters.Variables.Length].Fill(2)
            );

            var population = new Population(50, 50, chromosome);

            var fitness = new FunctionMinimumFitness()
            {
                FunctionVariables = parameters.Variables,
                Expression = parameters.Expression
            };

            var geneticAlgorithm = new GeneticAlgorithm(population, fitness, parameters.Selection, parameters.Crossover, parameters.Mutation)
            {
                Termination = parameters.Termination
            };

            var filepath = "./results_" + (parameters.AdaptiveOn ? "AGA" : "SGA") +
                "_" + parameters.Selection.GetType().Name +
                "_" + parameters.Crossover.GetType().Name +
                "_" + parameters.Mutation.GetType().Name +
                "_" + parameters.Termination.GetType().Name + ".csv";
            geneticAlgorithm.GenerationRan += new WriterEventHandler(filepath).Handle;

            geneticAlgorithm.GenerationRan += new ConsoleLogEventHandler(parameters.Variables).Handle;

            if (parameters.AdaptiveOn)
            {
                geneticAlgorithm.GenerationRan += new AdaptiveStrategyEventHandler().Handle;
            }

            geneticAlgorithm.Start();

            var finalPhenotype = (geneticAlgorithm.BestChromosome as FloatingPointChromosome).ToFloatingPoints();

            var finalVariableValues = "Parameters:";
            for (int i = 0; i < parameters.Variables.Length; i++)
            {
                finalVariableValues += "\n" + parameters.Variables[i] + " = " + finalPhenotype[i];
            }

            var finalFitness = (geneticAlgorithm.BestChromosome as FloatingPointChromosome).Fitness.Value;

            Console.WriteLine("\n\n- - - Final result: - - -" +
                "\nNumber of generations: " + geneticAlgorithm.GenerationsNumber +
                "\n\nFitness: " + finalFitness +
                "\n\n" + finalVariableValues +
                "\n\nRange: " + parameters.LowerBound + ", " + parameters.UpperBound +
                "\n\nf(" + String.Join(", ", parameters.Variables) + ") = " + parameters.Expression +
                " = " + (-finalFitness));

            Console.ReadKey();
        }
    }
}
