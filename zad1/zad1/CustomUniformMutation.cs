using GeneticSharp.Domain.Mutations;
using GeneticSharp.Domain.Randomizations;
using System;
using System.Collections.Generic;
using System.Linq;

namespace zad1
{
    public class CustomUniformMutation : UniformMutation
    {
        const int NUMBER_OF_BITS = 2 * 8 * sizeof(float);

        int[] MutableGenesIndexes { get; set; }

        private static Random rand = new Random();

        private CustomUniformMutation(int[] mutableGenesIndexes) : base(mutableGenesIndexes)
        {
            MutableGenesIndexes = mutableGenesIndexes;
        }

        public CustomUniformMutation GenerateAdaptedMutation()
        {
            for (int i = 0; i < MutableGenesIndexes.Length; i++)
            {
                if (MutableGenesIndexes[i] == 1)
                {
                    MutableGenesIndexes[i] = 0;
                    break;
                }
            }

            return new CustomUniformMutation(MutableGenesIndexes);
        }

        public static CustomUniformMutation Create()
        {
            IEnumerable<int> mutableGenesIndexes = from bit in Enumerable.Range(0, NUMBER_OF_BITS) select RandomInt();
            return new CustomUniformMutation(mutableGenesIndexes.ToArray());
        }

        private static int RandomInt()
        {
            return Convert.ToInt32(rand.NextDouble() >= 0.5);
        }
    }
}
