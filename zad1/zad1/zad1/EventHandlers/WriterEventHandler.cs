using GeneticSharp.Domain;
using GeneticSharp.Domain.Chromosomes;
using System;
using System.IO;

namespace zad1.EventHandlers
{
    public class WriterEventHandler : IEventHandler
    {
        private readonly string Filepath;

        public WriterEventHandler(string filepath)
        {
            Filepath = filepath;

            if (File.Exists(filepath))
                File.Delete(filepath);
        }

        public void Handle(object sender, EventArgs e)
        {
            var geneticAlgorithm = sender as GeneticAlgorithm;
            var bestChromosome = geneticAlgorithm.BestChromosome as FloatingPointChromosome;
            var bestFitness = bestChromosome.Fitness.Value;

            File.AppendAllText(
                Filepath, bestFitness.ToString(
                    "0.000", System.Globalization.CultureInfo.InvariantCulture) + '\n');
        }
    }
}
