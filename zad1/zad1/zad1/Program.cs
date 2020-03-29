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
            ParameterSelection parameters = ConsoleParameterSelectionFactory.createSelection();

            var chromosome = new FloatingPointChromosome(
                new double[parameters.Names.Length].Fill(parameters.LowerBound),
                new double[parameters.Names.Length].Fill(parameters.UpperBound),
                new int[parameters.Names.Length].Fill(2 * 8 * Marshal.SizeOf(parameters.LowerBound)),
                new int[parameters.Names.Length].Fill(0));
            var population = new Population(50, 100, chromosome);
            var fitness = new FuncFitness(genotype =>
            {
                var phenotype = (genotype as FloatingPointChromosome).ToFloatingPoints();

                Argument[] elements = new Argument[parameters.Names.Length];
                for (int i = 0; i < elements.Length; i++)
                {
                    elements[i] = new Argument(parameters.Names[i], phenotype[i]);
                }

                return new Expression(parameters.Expression, elements).calculate();
            });

            var geneticAlgorithm = new GeneticAlgorithm(population, fitness, parameters.Selection, parameters.Crossover, parameters.Mutation)
            {
                Termination = parameters.Termination
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

                    var coords = "";
                    for (int i = 0; i < parameters.Names.Length; i++)
                    {
                        coords += "\n  " + parameters.Names[i] + "\t" + phenotype[i] + ",\t";

                        coords = coords.TrimEnd(',', ' ', '\t');
                    }
                    Console.WriteLine(
                        "Generation " + geneticAlgorithm.GenerationsNumber + " : \tbest fitness = " + bestFitness + coords
                    );
                }
            };
            geneticAlgorithm.Start();

            Console.WriteLine("\nDone");
            Console.ReadKey();
        }
    }
}
