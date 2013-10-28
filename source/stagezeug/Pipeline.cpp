#include <stagezeug/Pipeline.h>

#include <algorithm>

namespace zeug {

Pipeline::Pipeline()
: m_dependenciesSorted(false)
{
}

Pipeline::~Pipeline()
{
	for (AbstractStage* stage: m_stages)
	{
		delete stage;
	}
}

void Pipeline::addStage(AbstractStage* stage)
{
    m_stages.push_back(stage);
    stage->dependenciesChanged.connect([this]() { m_dependenciesSorted = false; });
}

const std::vector<AbstractStage*>& Pipeline::stages() const
{
	return m_stages;
}

void Pipeline::execute()
{
    if (!m_dependenciesSorted)
    {
        sortDependencies();
    }
	
    for (AbstractStage* stage: m_stages)
    {
        stage->execute();
    }
}

void Pipeline::sortDependencies()
{
    std::sort(m_stages.begin(), m_stages.end(), [](AbstractStage* stage1, AbstractStage* stage2) {
        return stage2->dependsOn(stage1);
    });
    m_dependenciesSorted = true;
}

} // namespace zeug
