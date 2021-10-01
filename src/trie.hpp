#include <vector>
#include <cstdint>
#include <memory>

class uint16_trie {
    struct INode {
    public:
        virtual ~INode() = default;

        virtual void insert(uint16_t v) = 0;

        virtual bool has(uint16_t v) const = 0;

        virtual void create_tree(int level) = 0;
    };

    struct Leaf_node : public INode {
        bool contains_;

        Leaf_node() : contains_() {}

        void insert(uint16_t v) override {
            contains_ = true;
        }

        bool has(uint16_t v) const override {
            return contains_;
        }

        void create_tree(int level) override {}
    };

    struct Inner_node : public INode {
        std::vector<std::unique_ptr<INode>> children_;

        void insert(uint16_t v) override {
            children_[v >> 12]->insert(v << 4);
        }

        bool has(uint16_t v) const override {
            return children_[v >> 12]->has(v << 4);
        }

        void create_tree(int level) override {
            if (level == 1) {
                for (int i = 0; i < 16; i++) {
                    children_.emplace_back(std::make_unique<Leaf_node>());
                }
                return;
            }
            for (int i = 0; i < 16; i++) {
                children_.emplace_back(std::make_unique<Inner_node>());
                children_[children_.size() - 1]->create_tree(level - 1);
            }
        }
    };

    std::unique_ptr<INode> root_;
public:
    uint16_trie() {
        root_ = std::make_unique<Inner_node>();
        root_->create_tree(4);
    };

    void insert(uint16_t v) {
        root_->insert(v);
    }

    template<class T>
    void merge(const T &other) {
        for (int i = 0; i <= 0xFFFF; i++) {
            if (other.has(i)) {
                root_->insert(i);
            }
        }
    }

    bool has(uint16_t v) const {
        return root_->has(v);
    }
};