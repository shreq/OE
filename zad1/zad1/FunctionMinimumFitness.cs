using GeneticSharp.Domain.Chromosomes;
using GeneticSharp.Domain.Fitnesses;
using org.mariuszgromada.math.mxparser;
using System;

namespace zad1
{
    class FunctionMinimumFitness : IFitness
    {
        public string[] FunctionVariables { get; set; }
        public string Expression { get; set; }

        public double Evaluate(IChromosome genotype)
        {
            var phenotype = (genotype as FloatingPointChromosome).ToFloatingPoints();
            var elements = new Argument[FunctionVariables.Length];

            for (int i = 0; i < elements.Length; i++)
            {
                elements[i] = new Argument(FunctionVariables[i], phenotype[i]);
            }

            var result = new Expression(Expression, elements).calculate();

            if (double.IsNaN(result))
            {
                throw new NotFiniteNumberException("Fitness is NaN. Check expression string");
            }

            return -result;
        }
    }
}
